/*
 * _COPYRIGHT_
*
* File Name:Device.h
* System Environment: GNU/Linux
* Created Time:2012-10-15
* Author: Johan
* E-mail: Johaness@qq.com
* Description: 
*
*/

#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "Actions.h"

int Init_Upnp(void);
int Stop_Upnp(void);
static int Open_Drivers(void);
static int DeviceStateTableInit(char *DescDocURL);
static int CallbackEventHandler(Upnp_EventType,void *Event,void *Cookie);
static int SubscriptionRequest(struct Upnp_Subscription_Request *event);
int SetServiceTableVar(unsigned int service, int variable, char *value);
static int ActionRequest(struct Upnp_Action_Request *event);
extern struct _Service Service[SERVICE_MUN];

#endif //__DEVICE_H__
