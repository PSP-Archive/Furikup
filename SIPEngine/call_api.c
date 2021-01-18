
#include <pspkernel.h>
#include <pspusb.h>
#include <netinet/in.h>
#include <eXosip2/eXosip.h>
#include <osipparser2/osip_headers.h>
#include <pspusbcam.h>
#include <stdlib.h>
#include <ortp/stun.h>

#include "sipengine.h"
#include "config.h"
#include "call_api.h"
#include "audio.h"
#include "codec.h"
#include "presence.h"
#include "video.h"


char localSdp[4096];

enum CALL_STATES
{
	eNOT_REGISTERED	= 0,
	eREGISTERING	= 1,
	eREGISTERED		= 2,
	eIN_CALL		= 3,
	eINCOMING_CALL	= 4,
	eANSWERED		= 5,
	eDISCONNECTING  = 6,
};

int currentState = eNOT_REGISTERED;
SceUID callThid = 0;
SceUID cbid = 0;
int quit = 0;
int cid = 0;
int did = 0;
int tid = 0;
int rid = 0;
int callback_done = 0;
extern SceUID logfd;

void (*callback_proc)(char *information) = 0;

void ChangeState(int state);

struct EngineEvent
{
	int EventID;
	va_list argp;
};

int SIPEngineDoEvent(int EventID, ...)
{
	int     lReturn = 0;
	struct EngineEvent event;
	va_list argp;

	va_start(argp, EventID);

	event.EventID = EventID;
	event.argp = argp;

	if (cbid > 0)
	{
		lReturn = sceKernelNotifyCallback(cbid, (int)&event);

		while(!callback_done)
		{
			sceKernelDelayThread(1000);
		}
	}

	callback_done = 0;

	va_end(argp);
	
	return lReturn;
}

int GuiCallback(int arg1, struct EngineEvent *event, void *common) 
{
	int lReturn = SUI_RC_OK;

	int done = 1;

	switch (event->EventID)
	{
		case SUI_OUT_EVENT_NEW_CALL:
		{
			char* lAddress  = va_arg(event->argp, char*);
			char  lNewAddress[128];

			/* Check for known uri schemes.  If none present, add default
			   'sip:' scheme to the URI */
			if ((strncmp(lAddress, "sip:", 4) != 0) &&
					(strncmp(lAddress, "tel:", 4) != 0))
			{
				sprintf(lNewAddress, "sip:%s", lAddress);
				lAddress = lNewAddress;
			}
			
			InfoMessage("Call '%s'", lAddress);
			
			makeCall(lAddress);
			
			break;
		}

		case SUI_OUT_EVENT_ANSWER:
		{
			answerCall();

			break;
		}

		case SUI_OUT_EVENT_REJECT:
		case SUI_OUT_EVENT_HANGUP:
		{
			hangupCall();
			
			break;
		}

		case SUI_OUT_EVENT_CHANGE_PRESENCE:
		{
			int presence = va_arg(event->argp, int);

			update_presence(presence);

			break;
		}

		case SUI_OUT_EVENT_SHUTDOWN:
		{
			disconnectSipServer();
			done = 0;
			
			break;
		}

		default:
		{
			lReturn = SUI_RC_UNKNOWN_EVENT;
			
			break;
		}
	}

	callback_done = done;

	return lReturn;
}

int CallThread(SceSize args, void *argp)
{
	osip_message_t *reg = NULL;
	eXosip_event_t *je;
	int id;

	cbid = sceKernelCreateCallback("GuiCallback", (void*) GuiCallback, NULL);

	gEventFunction(SUI_IN_EVENT_STARTUP, SUI_STARTUP_STATE_BOOT);

	while(!quit)
	{
		sceKernelDelayThreadCB(100);
		if (currentState == eNOT_REGISTERED)
		{			
			eXosip_lock ();
			
			char *user_uri = config_get_user_uri();
			char *server_uri = config_get_server_uri();
			id = eXosip_register_build_initial_register(user_uri, 
														server_uri, NULL,
														120, &reg);
			
			if (id < 0)
			{
				eXosip_unlock ();
				return -1;
			}
			
			osip_message_set_allow(reg, "INVITE, ACK, CANCEL, BYE, OPTIONS, REFER, SUBSCRIBE, NOTIFY, MESSAGE, INFO");
			
			eXosip_register_send_register(id, reg);
			
			eXosip_unlock();

			gEventFunction(SUI_IN_EVENT_STARTUP, SUI_STARTUP_STATE_REGISTER);

			ChangeState(eREGISTERING);
		}

		je = eXosip_event_wait (0, 50);

		eXosip_lock();
		eXosip_automatic_refresh ();
		eXosip_automatic_action ();
		eXosip_unlock();

		if (je == NULL)
		{
			continue;
		}

		InfoMessage(je->textinfo);

		if(je->response)
		{
			printf("response = '%i'\n",je->response->status_code);
		}

		switch(currentState)
		{
			case eREGISTERING:
			{
				switch (je->type)
				{
					case EXOSIP_REGISTRATION_SUCCESS:
					{
						if (callback_proc)
						{
							InfoMessage("registered fine");
							callback_proc("Registered with SIP server");
						}

						rid = je->rid;

//						update_presence(SUI_PRESENCE_ONLINE);

						gEventFunction(SUI_IN_EVENT_STARTUP, SUI_STARTUP_STATE_READY);
						
						ChangeState(eREGISTERED);

						break;
					}
#if 0
					case EXOSIP_REGISTRATION_FAILURE:
					{
						sceKernelDelayThread(5*1000*1000);

						ChangeState(eNOT_REGISTERED);

						break;
					}
#endif
					default:
					{
						break;
					}
				}

				break;
			}

			case eREGISTERED:
			{
				switch (je->type)
				{
					case EXOSIP_CALL_INVITE:
					{
						eXosip_lock ();
						eXosip_call_send_answer (je->tid, 180, NULL);
						eXosip_unlock ();

						cid = je->cid;
						did = je->did;
						tid = je->tid;

						struct osip_from *from = osip_message_get_from(je->request);
						
						InfoMessage("New call from %s", from->displayname);

						gEventFunction(SUI_IN_EVENT_INCOMING_CALL, from->displayname, -1);
						
						osip_from_free(from);

						ChangeState(eINCOMING_CALL);

						break;
					}

					case EXOSIP_SUBSCRIPTION_NOTIFY:
					{
						osip_body_t *body = NULL;
						osip_message_get_body(je->request, 0, &body);

						if (body)
						{
							InfoMessage("presence=%d", parse_presence(body->body));
						}

						break;
					}

					case EXOSIP_IN_SUBSCRIPTION_NEW:
					{
						osip_message_t *answer;
						int i;

						eXosip_lock ();
						i = eXosip_insubscription_build_answer (je->tid, 202, &answer);
						if (i == 0)
						{
							i = eXosip_insubscription_send_answer (je->tid, 202, answer);
						}
						if (i != 0)
						{
							i = eXosip_insubscription_send_answer (je->tid, 400, NULL);
							return 0;
						}
						eXosip_unlock ();

#if 0
						sceKernelDelayThread(100);

						eXosip_lock ();

						/* send initial notify */
						i = _eXosip_insubscription_auto_send_notify(je->did , EXOSIP_SUBCRSTATE_ACTIVE, PROBATION);
						if (i != 0)
						{
							/* delete subscription... */
							return 0;
						}
						eXosip_unlock ();
#endif

						break;
					}

					default:
					{
						break;
					}
				}

				break;
			}

			case eIN_CALL:
			case eINCOMING_CALL:
			{
				switch (je->type)
				{
					case EXOSIP_CALL_RINGING:
					{
						InfoMessage("Phone is ringing");

						cid = je->cid;
						did = je->did;
						
						playRingback();

						break;
					}

					case EXOSIP_CALL_ANSWERED:
					{
						if (callback_proc)
						{
							callback_proc("Call answered");
						}

						osip_message_t *ack;

						eXosip_lock ();
						eXosip_call_build_ack(je->did, &ack);
						eXosip_call_send_ack(je->did, ack);
						eXosip_unlock ();

						rtpAudioSetup(je->tid, 0);
						rtpVideoSetup(je->tid, 0);

						ChangeState(eANSWERED);

						break;
					}

					case EXOSIP_SUBSCRIPTION_NOTIFY:
					{
						osip_body_t *body = NULL;
						osip_message_get_body(je->request, 0, &body);

						if (body)
						{
							InfoMessage("presence=%d", parse_presence(body->body));
						}

						break;
					}

					case EXOSIP_IN_SUBSCRIPTION_NEW:
					{
						osip_message_t *answer;
						int i;

						eXosip_lock ();
						i = eXosip_insubscription_build_answer (je->tid, 202, &answer);
						if (i == 0)
						{
							i = eXosip_insubscription_send_answer (je->tid, 202, answer);
						}
						if (i != 0)
						{
							i = eXosip_insubscription_send_answer (je->tid, 400, NULL);
							return 0;
						}
						eXosip_unlock ();

#if 0
						sceKernelDelayThread(100);

						eXosip_lock ();
						/* send initial notify */
						i = _eXosip_insubscription_auto_send_notify(je->did , EXOSIP_SUBCRSTATE_ACTIVE, PROBATION);
						if (i != 0)
						{
							/* delete subscription... */
							return 0;
						}
						eXosip_unlock ();
#endif

						break;
					}

					case EXOSIP_CALL_ACK:
					{
						cid = je->cid;
						did = je->did;

						rtpAudioSetup(je->tid, 1);
						rtpVideoSetup(je->tid, 1);

						ChangeState(eANSWERED);

						break;
					}

					case EXOSIP_CALL_CLOSED:
					{
						ChangeState(eREGISTERED);

						break;
					}

					case EXOSIP_CALL_SERVERFAILURE:
					case EXOSIP_CALL_GLOBALFAILURE:
					case EXOSIP_CALL_CANCELLED:
					case EXOSIP_CALL_TIMEOUT:
					{
						ErrorMessage("Call failed");

						ChangeState(eREGISTERED);

						break;
					}

					default:
					{
						break;
					}
				}

				break;
			}

			case eANSWERED:
			{
				switch (je->type)
				{
					case EXOSIP_CALL_INVITE:
					{
						break;
					}
		
					case EXOSIP_CALL_CLOSED:
					{
						if (callback_proc)
						{
							callback_proc("Call cleared");
						}

						// Stop the audio
						rtpAudioStop();
						rtpVideoStop();

						cid = 0;
						tid = 0;
						did = 0;

						ChangeState(eREGISTERED);
						break;
					}

					default:
					{
						break;
					}
				}

				break;
			}

			case eDISCONNECTING:
			{
				switch (je->type)
				{
					case EXOSIP_REGISTRATION_SUCCESS:
					case EXOSIP_REGISTRATION_TERMINATED:
					{
						ChangeState(eNOT_REGISTERED);
						quit = 1;

						break;
					}

					default:
					{
						break;
					}
				}

				break;
			}
		}
	}

	sceIoClose(logfd);

	callback_done = 1;

	sceKernelExitDeleteThread(0);

	return 0;
}

void ChangeState(int state)
{
	switch (state)
	{
		case eNOT_REGISTERED:
		{
			gEventFunction(SUI_IN_EVENT_SIP_STATE, SUI_SIP_STATE_DISCONNECTED);
			break;
		}
		case eREGISTERING:
		{
			gEventFunction(SUI_IN_EVENT_SIP_STATE, SUI_SIP_STATE_CONNECTING);
			break;
		}
		case eREGISTERED:
		{
			stopRingback();
			gEventFunction(SUI_IN_EVENT_SIP_STATE, SUI_SIP_STATE_CONNECTED);
			break;
		}
		case eIN_CALL:
		{
			gEventFunction(SUI_IN_EVENT_SIP_STATE, SUI_SIP_STATE_TRYING);
			break;
		}
		case eINCOMING_CALL:
		{
			gEventFunction(SUI_IN_EVENT_SIP_STATE, SUI_SIP_STATE_INCOMING);
			break;
		}
		case eANSWERED:
		{
			stopRingback();
			gEventFunction(SUI_IN_EVENT_SIP_STATE, SUI_SIP_STATE_ESTABLISHED);
			break;
		}
	}

	currentState = state;
}

int setupCallThread(void)
{
	callThid = sceKernelCreateThread("SipThread", CallThread, 0x18, 0x10000, 0, NULL);
	sceKernelStartThread(callThid, 0, 0);

	return callThid;
}

char sdp[4096];

int makeCall(char *user)
{
	InfoMessage("new call");
	if (currentState == eREGISTERED)
	{	
		osip_message_t *invite;
		
		eXosip_call_build_initial_invite (&invite,
					  user,
					  config_get_user_uri(),
					  NULL,
					  "");
		if (!invite)
		{
			ErrorMessage("Failed invite build");
			return -1;
		} 

		createLocalSdp(sdp, 0);

		osip_message_set_body(invite, sdp, strlen (sdp));
		osip_message_set_content_type(invite, "application/sdp");

		eXosip_lock();
		eXosip_call_send_initial_invite(invite);
		InfoMessage("Sent invite");
		eXosip_unlock();

		ChangeState(eIN_CALL);
		
		InfoMessage("Now in call");
	}
	
	return 0;
}

void disconnectSipServer()
{
	osip_message_t *reg = NULL;

	if ((currentState == eIN_CALL) || (currentState == eANSWERED))
	{
		hangupCall();
		sceKernelDelayThread(1000);
	}
	
	if (currentState == eREGISTERED)
	{
		ChangeState(eDISCONNECTING);

		eXosip_lock();
		eXosip_register_build_register(rid, 0, &reg);
		eXosip_register_send_register(rid, reg);
		eXosip_lock();
	}
	else
	{
		if (callThid > 0)
		{
			quit = 1;
		}
		else
		{
			sceIoClose(logfd);

			callback_done = 1;
		}
	}
}

void answerCall(void)
{
	osip_message_t *ans;
	sdp_message_t *rem_sdp;

	if (currentState == eINCOMING_CALL)
	{
		eXosip_lock();
		eXosip_call_build_answer (tid, 200, &ans);

		rem_sdp = eXosip_get_remote_sdp_from_tid(tid);
		createLocalSdp(sdp, rem_sdp);

		osip_message_set_body(ans, sdp, strlen (sdp));
		osip_message_set_content_type(ans, "application/sdp");

		eXosip_call_send_answer (tid, 0, ans);

		eXosip_unlock();
	}
}

void hangupCall(void)
{
	if (currentState == eANSWERED)
	{
		rtpAudioStop();
		rtpVideoStop();
	}

	if ((currentState == eIN_CALL) ||
			(currentState == eANSWERED) ||
		  (currentState == eINCOMING_CALL))
	{
		eXosip_lock();
		eXosip_call_terminate(cid, did);
		eXosip_unlock();

		cid = 0;
		did = 0;

		ChangeState(eREGISTERED);
	}
}

void UpdateFirewallAddr(osip_message_t * sip)
{
	if(sip)
	{
		int firewall_port = 0;

		osip_via_t *via = NULL;
		osip_generic_param_t *br;

		osip_message_get_via (sip, 0, &via);

		if(via)
		{
            osip_via_param_get_byname (via, "rport", &br);
            if (br != NULL && br->gvalue != NULL)
            {
                firewall_port = atoi(br->gvalue);

				osip_via_param_get_byname (via, "received", &br);
				if (br != NULL && br->gvalue != NULL
					&& sip->from!=NULL && sip->from->url!=NULL
					&& sip->from->url->host!=NULL)
				{
					eXosip_masquerade_contact(br->gvalue, firewall_port);
				}
            }
			
		}
	}
}

void registerCallbackProc(void *proc)
{
	callback_proc = proc;
}
