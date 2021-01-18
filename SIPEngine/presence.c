
#include <eXosip2/eXosip.h>

#include "sipengineif.h"
#include "config.h"
#include "presence.h"

char buf[5000];

void update_presence(int status)
{
	osip_message_t *pub;
	char activity[25];
	char note[25];
	char state[25];
	char from[255];
	int i;

	strcpy(from, config_get_user_uri());
	strcpy(state, "open");

	switch (status)
	{
		case SUI_PRESENCE_OFFLINE:
		{
			strcpy(state, "closed");
			strcpy(activity, "<es:activities>\n\
  <es:activity>permanent-absence</es:activity>\n\
</es:activities>\n");
			break;
		}

		case SUI_PRESENCE_ONLINE:
		{
			strcpy(note, "<note>online</note>\n");
			break;
		}

		case SUI_PRESENCE_BUSY:
		{
			strcpy(activity, "<es:activities>\n\
  <es:activity>busy</es:activity>\n\
</es:activities>\n");
			strcpy(note, "<note>busy</note>\n");
			break;
		}

		case SUI_PRESENCE_AWAY:
		{
			strcpy(activity, "<es:activities>\n\
  <es:activity>away</es:activity>\n\
</es:activities>\n");
			strcpy(note, "<note>away</note>\n");
			break;
		}

		case SUI_PRESENCE_ON_PHONE:
		{
			strcpy(activity, "<es:activities>\n\
  <es:activity>on-the-phone</es:activity>\n\
</es:activities>\n");
			strcpy(note, "<note>On the phone</note>\n");
			break;
		}

		default:
		{
			return;
		}
	}

	snprintf(buf, 5000, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<presence xmlns=\"urn:ietf:params:xml:ns:pidf\"\n\
          xmlns:es=\"urn:ietf:params:xml:ns:pidf:status:rpid-status\"\n\
          entity=\"%s\">\n\
<tuple id=\"sg89ae\">\n\
<status>\n\
<basic>%s</basic>\n\
%s\
</status>\n\
<contact priority=\"0.8\">%s</contact>\n\
%s\
</tuple>\n\
</presence>",
	      from, state, activity, from, note);

	i = eXosip_build_publish(&pub, (char *)from, (char *)from, NULL, "presence", "1800", "application/pidf+xml", buf);
	if (i<0)
	{
		return;
	}

	eXosip_lock();
	i = eXosip_publish(pub, from); /* should update the sip-if-match parameter
									from sip-etag  from last 200ok of PUBLISH */
	eXosip_unlock();
}

int parse_presence(char *body)
{
	if (body!=NULL)
	{
		/* search for the open string */
		char *tmp = body;
		while (tmp[0]!='\0')
	    {
			if (tmp[0]=='o' && 0==osip_strncasecmp(tmp, "open", 4))
			{
				/* search for the contact entry */
				while (tmp[0]!='\0')
				{
					if (tmp[0]=='a' && 0==osip_strncasecmp(tmp, "away", 4))
						return SUI_PRESENCE_AWAY;
					else if (tmp[0]=='b' && 0==osip_strncasecmp(tmp, "busy", 4))
						return SUI_PRESENCE_BUSY;
					else if (tmp[0]=='o' && 0==osip_strncasecmp(tmp, "on-the-phone", 12))
						return SUI_PRESENCE_ON_PHONE;

					if (tmp[0]=='/' && 0==osip_strncasecmp(tmp, "/status", 7))
					{
						return SUI_PRESENCE_ONLINE;
					}
					tmp++;
				}

				break;
			}
			else if (tmp[0]=='c' && 0==osip_strncasecmp(tmp, "closed", 6))
			{
				return SUI_PRESENCE_OFFLINE;
				break;
			}
			tmp++;
		}
	}

	return SUI_PRESENCE_OFFLINE;
}
