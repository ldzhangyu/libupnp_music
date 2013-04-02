/*
 * _COPYRIGHT_
 *
 * File Name: ActionExec.c
 * System Environment: GNU/Linux
 * Created Time: 2012-10-20
 * Author: Johan
 * E-mail: Johaness@qq.com
 * Description: 
 *
 */

#include "Actions.h"
#include "Core.h"
#include "Device.h"

int SetAVTransportURI(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{
    char *ID = NULL;
    char *URI = NULL;
    char *URIMetaData = NULL;

    (*out) = NULL;
    (*errorString) = NULL;

    PMSG("exec---> %s() \n",__FUNCTION__);

    if (!(ID = (char *)GetFirstDocumentItem(in, "InstanceID"))) 
    {
	(*errorString) = "Invalid Value";
	return UPNP_E_INVALID_PARAM;
    }

    if (!(URI = (char *)GetFirstDocumentItem(in, "CurrentURI"))) 
    {
	(*errorString) = "Invalid Value";
	return UPNP_E_INVALID_PARAM;
    }

    if (!(URIMetaData = (char *)GetFirstDocumentItem(in, "CurrentURIMetaData"))) 
    {
	(*errorString) = "Invalid Value";
	return UPNP_E_INVALID_PARAM;
    }

    if(SetServiceTableVar(Ser_Id,A_ARG_TYPE_InstanceID,ID) && SetServiceTableVar(Ser_Id,AVTransportURI,URI) && SetServiceTableVar(Ser_Id,AVTransportURIMetaData,URIMetaData)) 
    {
	if (UpnpAddToActionResponse(out, Service[Ser_Id].Action->Name[pos], ServiceType[Ser_Id], Service[Ser_Id].State->Name[AVTransportURI], URI) != UPNP_E_SUCCESS) 
	{
	    (*out) = NULL;
	    (*errorString) = "Internal Error";
	    return UPNP_E_INTERNAL_ERROR;
	}

	Core_set_uri(URI);

	return UPNP_E_SUCCESS;
    } else {
	(*errorString) = "Internal Error";
	return UPNP_E_INTERNAL_ERROR;
    }

    return UPNP_E_SUCCESS;
}

int SetNextAVTransportURI(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetMediaInfo(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetMediaInfo_Ext(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetTransportInfo(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetPositionInfo(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetDeviceCapabilities(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetTransportSettings(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int Stop(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{
    char *ID = NULL;

    (*out) = NULL;
    (*errorString) = NULL;

    PMSG("exec---> %s() \n",__FUNCTION__);

    if (!(ID = (char *)GetFirstDocumentItem(in, "InstanceID"))) 
    {
	(*errorString) = "Invalid Value";
	return UPNP_E_INVALID_PARAM;
    }

    if(SetServiceTableVar(Ser_Id,A_ARG_TYPE_InstanceID,ID)) 
    {
	if (UpnpAddToActionResponse(out, Service[Ser_Id].Action->Name[pos], ServiceType[Ser_Id], Service[Ser_Id].State->Name[A_ARG_TYPE_InstanceID], ID) != UPNP_E_SUCCESS) 
	{
	    (*out) = NULL;
	    (*errorString) = "Internal Error";
	    return UPNP_E_INTERNAL_ERROR;
	}

	Core_stop();

	return UPNP_E_SUCCESS;
    } else {
	(*errorString) = "Internal Error";
	return UPNP_E_INTERNAL_ERROR;
    }
    
    return UPNP_E_SUCCESS;
}

int Play(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{
    char *ID = NULL;
    char *SPEED = NULL;

    (*out) = NULL;
    (*errorString) = NULL;

    PMSG("exec---> %s() \n",__FUNCTION__);

    if (!(ID = (char *)GetFirstDocumentItem(in, "InstanceID"))) 
    {
	(*errorString) = "Invalid Value";
	return UPNP_E_INVALID_PARAM;
    }

    if (!(SPEED = (char *)GetFirstDocumentItem(in, "Speed"))) 
    {
	(*errorString) = "Invalid Value";
	return UPNP_E_INVALID_PARAM;
    }

    if(SetServiceTableVar(Ser_Id,A_ARG_TYPE_InstanceID,ID) && SetServiceTableVar(Ser_Id,TransportPlaySpeed,SPEED)) 
    {
	if (UpnpAddToActionResponse(out, Service[Ser_Id].Action->Name[pos], ServiceType[Ser_Id], Service[Ser_Id].State->Name[TransportPlaySpeed], SPEED) != UPNP_E_SUCCESS) 
	{
	    (*out) = NULL;
	    (*errorString) = "Internal Error";
	    return UPNP_E_INTERNAL_ERROR;
	}

	Core_play();

	return UPNP_E_SUCCESS;
    } else {
	(*errorString) = "Internal Error";
	return UPNP_E_INTERNAL_ERROR;
    }

    return UPNP_E_SUCCESS;
}

int Pause(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int Record(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int Seek(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int Next(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int Previous(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SetPlayMode(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SetRecordQualityMode(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetCurrentTransportActions(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetDRMState(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetStateVariables(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SetStateVariables(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetProtocolInfo(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int PrepareForConnection(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int ConnectionComplete(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetCurrentConnectionIDs(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetCurrentConnectionInfo(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int ListPresets(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SelectPreset(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetBrightness(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SetBrightness(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetContrast(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SetContrast(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetSharpness(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SetSharpness(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetRedVideoGain(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SetRedVideoGain(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetGreenVideoGain(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SetGreenVideoGain(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetBlueVideoGain(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SetBlueVideoGain(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetRedVideoBlackLevel(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SetRedVideoBlackLevel(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetGreenVideoBlackLevel(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SetGreenVideoBlackLevel(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetBlueVideoBlackLevel(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SetBlueVideoBlackLevel(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetColorTemperature(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SetColorTemperature(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetHorizontalKeystone(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SetHorizontalKeystone(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetVerticalKeystone(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SetVerticalKeystone(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetMute(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SetMute(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetVolume(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SetVolume(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetVolumeDB(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SetVolumeDB(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetVolumeDBRange(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int GetLoudness(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int SetLoudness(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int XGetStateVariables(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{

    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}

int XSetStateVariables(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos)
{
    PMSG("exec---> %s()\n",__FUNCTION__);
    return UPNP_E_SUCCESS;
}
