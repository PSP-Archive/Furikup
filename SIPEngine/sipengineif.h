/*
 * Interface that every SIP Phone UI must implement.
 *
 * Note that any pointers present in event info are only valid
 * until the return from the event - so for example any string 
 * data should be copied via strcpy, rather than simple assignment.
 */

#ifndef SIPPHONE_UI_H
#define SIPPHONE_UI_H

/* Current version of the API */                                   
#define SUI_API_VERSION           1

/*
 * Return the version of this API implemented by this UI.
 * 
 * UI should return SUI_API_VERSION.
 * 
 * Some features of the API may only be available on future versions.  Currently the only
 * version is 1.
 */                          
int GetSIPAPIVersion(void);

typedef struct Contact
{
	char nickname[128];
	char firstname[128];
	char lastname[128];
	char sipuri[128];
} Contact;

typedef int (*SUI_OUT_EVENT_FN)(int EventID, ...);

/*
 * Initialise the UI, and store the set of callbacks.
 */
int PSPPhoneInitialize(SUI_OUT_EVENT_FN callback);

/*
 * Main interface function - do event.
 *
 * Responsible for performing appropriate action, based on the given event and parameters
 * (see SUI_IN_EVENT_* definitions below.)
 */
int PSPPhoneDoEvent(int EventID, ...);

/* --------------------- INPUT EVENTS -----------------------*/

/*
 * Event:  Incoming call - answer?
 * Params: 0: Caller address/number (char*)
 *         1: Contact index from addr book (int, -1 for unknown)
 * Return: null
 */
#define SUI_IN_EVENT_INCOMING_CALL   1

/*
 * Event:  Notify SIP connection state change
 * Params: 0: State code (int - see SUI_SIP_STATE_* below)
 * Return: null
 */
#define SUI_IN_EVENT_SIP_STATE       2
#define SUI_SIP_STATE_DISCONNECTED  0
#define SUI_SIP_STATE_CONNECTING    1
#define SUI_SIP_STATE_CONNECTED     2
#define SUI_SIP_STATE_TRYING        3
#define SUI_SIP_STATE_INCOMING      4
#define SUI_SIP_STATE_ESTABLISHED   5

/*
 * Event:  Display video packet
 * Params: TBD
 * Return: null
 */
#define SUI_IN_EVENT_VIDEO_FRAME     3

/*
 * Event:  Startup - the system is initializing
 * Params: 0: Startup state (int - see SUI_STARTUP_STATE_* below)
 * Return: null
 */
#define SUI_IN_EVENT_STARTUP         4
#define SUI_STARTUP_STATE_BOOT      0 
#define SUI_STARTUP_STATE_REGISTER  1
#define SUI_STARTUP_STATE_READY     2

/*
 * Event:  Presence info - a contact is online/offline etc.
 * Params: 0: Contact index
 *         1: Presence state (int - see SUI_PRESENCE_* below)
 * Return: null
 */
#define SUI_IN_EVENT_PRESENCE_UPDATE 5
#define SUI_PRESENCE_OFFLINE         0
#define SUI_PRESENCE_ONLINE          1
#define SUI_PRESENCE_BUSY            2
#define SUI_PRESENCE_AWAY            3
#define SUI_PRESENCE_ON_PHONE        4

/*
 * Event:  Address book - there is an address book available
 * Params: 0: Contact details (Contact *)
 * Return: null
 */
#define SUI_IN_ADDRESS_BOOK          6

/*
 * Event:  Info message - a general info message from the engine.
 *         The UI is not obliged to pass these on, the app should be
 *         functional enough without them.
 * Params: 0: message (char*)
 * Return: null
 */
#define SUI_IN_INFO_MESSAGE          7

/* 
 * Build an info message via printf-like interface (convenience function)
 */
void InfoMessage(const char *fmt, ...);

/*
 * Event:  Error message - an error string from the engine.
 *         The UI should display these if possible.
 * Params: 0: message (char*)
 * Return: null
 */
#define SUI_IN_ERROR_MESSAGE         8

/* 
 * Build an error message via printf-like interface (convenience function)
 */
void ErrorMessage(const char *fmt, ...);


 
/* --------------------- OUTPUT EVENTS -----------------------*/

/* 
 * Event:  User wants to hangup the phone
 * Params: None
 * Return: null
 */
#define SUI_OUT_EVENT_HANGUP           0

/* Event:  User wants to make a new phone call 
 * Params: 0: SIP URI to call (char*)
 * Return: null
 */
#define SUI_OUT_EVENT_NEW_CALL         1

/* Event:  User wants to answer the call
 * Params: None
 * Return: null
 */
#define SUI_OUT_EVENT_ANSWER           2

/* Event:  User wants to reject the call
 * Params: None
 * Return: null
 */
#define SUI_OUT_EVENT_REJECT           3

/* Event:  Change user's presence info
 * Params: 0: New presence state (int - see SUI_PRESENCE_*)
 * Return: null
 */
#define SUI_OUT_EVENT_CHANGE_PRESENCE  4

/* Return codes */
#define SUI_RC_OK                     0
#define SUI_RC_ANSWERCALL             1
#define SUI_RC_UNKNOWN_EVENT         -1

/* Event:  Shutdown the SIP engine
 * Params: none
 * Return: null
 */
#define SUI_OUT_EVENT_SHUTDOWN         5


/* Initialise the SIP engine.
 * Params: the callback block for the UI-supplied functions
 * Return: 0 if OK
 */
int SIPEngineInitialize(SUI_OUT_EVENT_FN callback);

/* Issue an OUT event to the SIP Engine
 * Params: 0: Event ID (see SUI_OUT_EVENT_* above)
 *         others as per the event
 * Return: as per the event
 */
int SIPEngineDoEvent(int EventID, ...);

const char *SIPEngineGetBuild(void);

#endif
