/*
* _COPYRIGHT_
*
* File Name:ActionExec.h
* System Environment: GNU/Linux
* Created Time:2012-10-20
* Author: Johan
* E-mail: Johaness@qq.com
* Description: 
*
*/

#ifndef __ACTIONEXEC_H__
#define __ACTIONEXEC_H__

#include "Struct.h"
#include <sys/stat.h>

int SetAVTransportURI(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetNextAVTransportURI(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetMediaInfo(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetMediaInfo_Ext(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetTransportInfo(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetPositionInfo(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetDeviceCapabilities(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetTransportSettings(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int Stop(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int Play(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int Pause(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int Record(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int Seek(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int Next(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int Previous(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetPlayMode(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetRecordQualityMode(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetCurrentTransportActions(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetDRMState(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetStateVariables(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetStateVariables(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetProtocolInfo(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int PrepareForConnection(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int ConnectionComplete(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetCurrentConnectionIDs(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetCurrentConnectionInfo(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);

int ListPresets(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SelectPreset(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetBrightness(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetBrightness(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetContrast(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetContrast(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetSharpness(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetSharpness(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetRedVideoGain(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetRedVideoGain(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetGreenVideoGain(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetGreenVideoGain(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetBlueVideoGain(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetBlueVideoGain(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetRedVideoBlackLevel(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetRedVideoBlackLevel(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetGreenVideoBlackLevel(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetGreenVideoBlackLevel(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetBlueVideoBlackLevel(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetBlueVideoBlackLevel(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetColorTemperature(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetColorTemperature(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetHorizontalKeystone(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetHorizontalKeystone(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetVerticalKeystone(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetVerticalKeystone(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetMute(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetMute(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetVolume(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetVolume(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetVolumeDB(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetVolumeDB(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetVolumeDBRange(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int GetLoudness(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int SetLoudness(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int XGetStateVariables(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);
int XSetStateVariables(IXML_Document * in, IXML_Document ** out,const char **errorString,int Ser_Id,int pos);

static upnp_action AVTransportExec[] = {
    SetAVTransportURI,
    SetNextAVTransportURI,
    GetMediaInfo,
    GetMediaInfo_Ext,
    GetTransportInfo,
    GetPositionInfo,
    GetDeviceCapabilities,
    GetTransportSettings,
    Stop,
    Play,
    Pause,
    Record,
    Seek,
    Next,
    Previous,
    SetPlayMode,
    SetRecordQualityMode,
    GetCurrentTransportActions,
    GetDRMState,
    GetStateVariables,
    SetStateVariables
};

static upnp_action ConnectionManagerExec[] = {
    GetProtocolInfo,
    PrepareForConnection,
    ConnectionComplete,
    GetCurrentConnectionIDs,
    GetCurrentConnectionInfo
};		

static upnp_action RenderingControlExec[] = {
    ListPresets,
    SelectPreset,
    GetBrightness,
    SetBrightness,
    GetContrast,
    SetContrast,
    GetSharpness,
    SetSharpness,
    GetRedVideoGain,
    SetRedVideoGain,
    GetGreenVideoGain,
    SetGreenVideoGain,
    GetBlueVideoGain,
    SetBlueVideoGain,
    GetRedVideoBlackLevel,
    SetRedVideoBlackLevel,
    GetGreenVideoBlackLevel,
    SetGreenVideoBlackLevel,
    GetBlueVideoBlackLevel,
    SetBlueVideoBlackLevel,
    GetColorTemperature,
    SetColorTemperature,
    GetHorizontalKeystone,
    SetHorizontalKeystone,
    GetVerticalKeystone,
    SetVerticalKeystone,
    GetMute,
    SetMute,
    GetVolume,
    SetVolume,
    GetVolumeDB,
    SetVolumeDB,
    GetVolumeDBRange,
    GetLoudness,
    SetLoudness,
   XGetStateVariables,
   XSetStateVariables
};		


static upnp_action *ActionExec[SERVICE_MUN] = {AVTransportExec,ConnectionManagerExec,RenderingControlExec};

#endif //__ACTIONEXEC_H__
