/*
 * _COPYRIGHT_
 *
 * File Name: Device.c
 * System Environment: GNU/Linux
 * Created Time: 2012-10-15
 * Author: Johan
 * E-mail: Johaness@qq.com
 * Description: 
 *
 */

#include "Device.h"

static ithread_mutex_t DevMutex = PTHREAD_MUTEX_INITIALIZER;
static char **ActionTables[SERVICE_MUN] = {AVTransportAction,ConnectionManagerAction,RenderingControlAction};
static char **StateTables[SERVICE_MUN] = {AVTransportState,ConnectionManagerState,RenderingControlState};
static char **DefaultVal[SERVICE_MUN] = {AVTransportVal,ConnectionManagerVal,RenderingControlVal};
struct _Service Service[SERVICE_MUN];

int Init_Upnp(void)
{
	int rc;
	unsigned short port = 0;
	char *ip_address = NULL;
	char DES_DOC_URL[200];

	rc = UpnpInit(ip_address, port);
	Initialize(printf);

	if (rc != UPNP_E_SUCCESS) 
	{
		PMSG("UpnpInit() Error: %d\n", rc);

		UpnpFinish();

		return ERROR;
	}

	if (!ip_address) 
	{
		ip_address = UpnpGetServerIpAddress();
	}

	if (!port) 
	{

		port = UpnpGetServerPort();
	}

	printf("\nUPnP Initialized\n""\tipaddress = %s port = %u\n", ip_address ? ip_address : "{NULL}", port);

	snprintf(DES_DOC_URL, 200, "http://%s:%d/%s", ip_address,port, DOC_NAME);

	ModifyXmlNodeValue("friendlyName",ip_address);

	printf("%s\n\n",DES_DOC_URL);

	rc = UpnpSetWebServerRootDir(WEB_PATH);

	if (rc != UPNP_E_SUCCESS) 
	{
		PMSG("Error registering CP: %d\n", rc);

		UpnpFinish();

		return ERROR;
	}

	rc = UpnpRegisterRootDevice(DES_DOC_URL, CallbackEventHandler, &pt_handle, &pt_handle);
	if (UPNP_E_SUCCESS != rc) 
	{
		PMSG("Error sending search request%d\n", rc);

		UpnpFinish();

		return ERROR;
	}
	else
	{
		DeviceStateTableInit(DES_DOC_URL);
		rc = UpnpSendAdvertisement(pt_handle, 0/*default_advr_expire*/);
		if (rc != UPNP_E_SUCCESS) 
		{
			UpnpFinish();
			return rc;
		}
	}

	return SUCCESS;
}

int Stop_Upnp(void)
{
	UpnpUnRegisterRootDevice(pt_handle);
	UpnpFinish();

	ithread_mutex_destroy(&DevMutex);
	return SUCCESS;
}

static int DeviceStateTableInit(char *DescDocURL)
{
	IXML_Document *DescDoc = NULL;
	int ret = UPNP_E_SUCCESS;
	int i = 0;
	int m = 0;
	char *Serv_Id = NULL;
	char *Evnt = NULL;
	char *Ctrl = NULL;
	char *UDN = NULL;

	if (UpnpDownloadXmlDoc(DescDocURL, &DescDoc) != UPNP_E_SUCCESS) 
	{
		PMSG("Error Parsing %s\n",DescDocURL);
		ret = UPNP_E_INVALID_DESC;
		goto error_handler;
	}

	UDN = (char *)GetFirstDocumentItem(DescDoc, "UDN");
	printf("UDN is %s\n", UDN);

	for(i = 0; i < SERVICE_MUN; i++)
	{

		if (!FindAndParseService(DescDoc, DescDocURL, ServiceType[i], &Serv_Id, &Evnt, &Ctrl)) 
		{
			PMSG("Error: Could not find Service: %s\n", ServiceType[i]);
			ret = UPNP_E_INVALID_DESC;
			goto error_handler;
		}

		strcpy(Service[i].UDN,UDN);
		strcpy(Service[i].Type,ServiceType[i]);
		strcpy(Service[i].Id,Serv_Id);

		Service[i].ActionCount = Service[i].ActionsCount = *(TablesMun + (i % SERVICE_MUN) + i);
		Service[i].StateCount = Service[i].DefvalCount =  *(TablesMun + (i % SERVICE_MUN) + i + 1);

		Service[i].Action = (struct _Action *)malloc(sizeof(struct _Action) + sizeof(unsigned char*) * (TablesMun[i + (i % SERVICE_MUN)]));

		Service[i].Actions = (struct _Actions *)malloc(sizeof(struct _Actions) + sizeof(unsigned char*) * (TablesMun[i + (i % SERVICE_MUN)]));

		printf("Serv_Id is %s;Evnt is %s; Ctrl is %s ac %d, sc %d\n", Serv_Id, Evnt, Ctrl, Service[i].ActionsCount, Service[i].DefvalCount); 
		for(m = 0; m < Service[i].ActionsCount; m++)
		{
			*(Service[i].Action->Name + m) = *(ActionTables[i]+m);
			*(Service[i].Actions->Exec + m) = (ActionExec[i]+m);
		}

		Service[i].State = (struct _State *)malloc(sizeof(struct _State) + sizeof(unsigned char*) * (TablesMun[i + (i % SERVICE_MUN) + 1]));
		Service[i].Defval = (struct _Defval *)malloc(sizeof(struct _Defval) + sizeof(unsigned char*) * (TablesMun[i + (i % SERVICE_MUN) + 1]));

		for(m = 0; m < Service[i].StateCount; m++)
		{
			*(Service[i].State->Name + m) = *(StateTables[i]+m);
			*(Service[i].Defval->Val + m) = *(DefaultVal[i]+m);
		}

		free(Serv_Id);
		Serv_Id = NULL;
		free(Evnt);
		Evnt = NULL;
		free(Ctrl);
		Ctrl = NULL;
	}

error_handler:
	if (UDN)
	{
		free(UDN);
		UDN = NULL;
	}
#if 0
	if (Serv_Id)
	{
		free(Serv_Id);
		Serv_Id = NULL;
	}
	if (Evnt)
	{
		free(Evnt);
		Evnt = NULL;
	}
	if (Ctrl)
	{
		free(Ctrl);
		Ctrl = NULL;
	}
#endif
	if (DescDoc)
	{
		ixmlDocument_free(DescDoc);
		DescDoc = NULL;
	}

	return (ret);
}

static int CallbackEventHandler(Upnp_EventType EventType, void *Event,	void *Cookie)
{
	switch (EventType) 
	{
		case UPNP_EVENT_SUBSCRIPTION_REQUEST: 
			SubscriptionRequest((struct Upnp_Subscription_Request *) Event);
			break;
		case UPNP_CONTROL_ACTION_REQUEST: 
			ActionRequest((struct Upnp_Action_Request *) Event);
			break;
		case UPNP_DISCOVERY_ADVERTISEMENT_ALIVE:
		case UPNP_DISCOVERY_SEARCH_RESULT:
		case UPNP_DISCOVERY_SEARCH_TIMEOUT:
		case UPNP_DISCOVERY_ADVERTISEMENT_BYEBYE:
		case UPNP_CONTROL_ACTION_COMPLETE:
		case UPNP_CONTROL_GET_VAR_COMPLETE:
		case UPNP_EVENT_RECEIVED:
		case UPNP_EVENT_RENEWAL_COMPLETE:
		case UPNP_EVENT_SUBSCRIBE_COMPLETE:
		case UPNP_EVENT_UNSUBSCRIBE_COMPLETE:
			break;
		default:
			PMSG("Error in %s: unknown event type %d\n",__FUNCTION__,EventType);
	}
	return 0;
}

static int SubscriptionRequest(struct Upnp_Subscription_Request *event)
{
	unsigned int i = 0;

	printf("SubscriptionRequest event %s\n", event->UDN);
	ithread_mutex_lock(&DevMutex);

	for (i = 0; i < SERVICE_MUN; ++i) 
	{
		if (strcmp(event->UDN, Service[i].UDN) == 0 && strcmp(event->ServiceId, Service[i].Id) == 0) 
		{
			UpnpAcceptSubscription(pt_handle, event->UDN, event->ServiceId, (const char **)Service[i].State->Name, (const char **)Service[i].Defval->Val, Service[i].StateCount, event->Sid);
		}
	}

	ithread_mutex_unlock(&DevMutex);

	return 1;
}

int SetServiceTableVar(unsigned int service, int variable, char *value)
{

	if(service >= SERVICE_MUN || variable >= Service[service].StateCount/* || strlen(value) >= 6*/)
	{
		return 0;
	}

	ithread_mutex_lock(&DevMutex);

	*(Service[service].Defval->Val + variable) = value;

	UpnpNotify(pt_handle,Service[service].UDN,Service[service].Id,(const char **)&Service[service].State->Name[variable],(const char **)&Service[service].Defval->Val[variable],1);

	ithread_mutex_unlock(&DevMutex);

	return 1;
}

static int ActionRequest(struct Upnp_Action_Request *event)
{
	int action_found = 0;
	int i = 0;
	int service = -1;
	int retCode = 0;
	const char *errorString = NULL;

	event->ErrCode = 0;
	event->ActionResult = NULL;

	for (i = 0; i < SERVICE_MUN; i++) 
	{
		if (strcmp(event->DevUDN, Service[i].UDN) == 0 && strcmp(event->ServiceID, Service[i].Id) == 0) 
		{
			service = i;
			break;
		}
	}

	for (i = 0; i < Service[service].ActionCount && Service[service].Action->Name[i] != NULL; i++) 
	{
		if (!strcmp(event->ActionName, Service[service].Action->Name[i])) 
		{
			retCode = (*(Service[service].Actions->Exec[i]))(event->ActionRequest,&event->ActionResult,&errorString,service,i);

#if 0
			errorString = "Error";
			retCode = UPNP_E_INTERNAL_ERROR;
#endif
			action_found = 1;

			break;
		}
	}

	if (!action_found) 
	{
		event->ActionResult = NULL;
		printf("Invalid Action\n");
		strcpy(event->ErrStr, "Invalid Action");
		event->ErrCode = 401;
	} 
	else 
	{
		if (retCode == UPNP_E_SUCCESS) 
		{
			event->ErrCode = UPNP_E_SUCCESS;
		} 
		else 
		{
			strcpy(event->ErrStr, errorString);
			switch (retCode) 
			{
				case UPNP_E_INVALID_PARAM:
					event->ErrCode = 402;
					break;
				case UPNP_E_INTERNAL_ERROR:
				default:
					event->ErrCode = 501;
					break;
			}
		}
	}

	return event->ErrCode;
}
