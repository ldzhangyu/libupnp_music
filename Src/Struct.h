/*
* _COPYRIGHT_
*
* File Name:Struct.h
* System Environment: GNU/Linux
* Created Time:2012-10-15
* Author: Johan
* E-mail: Johaness@qq.com
* Description: 
*
*/

#ifndef __STRUCT_H__
#define __STRUCT_H__

#include <stdio.h>
#include <errno.h>
#include <fcntl.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "upnp.h"
#include "upnptools.h"
#include "ithread.h"
#include "ixml.h"

#define TRUE 				1
#define FALSE 				0

#define SUCCESS 			0
#define ERROR 				(-1)
#define WARNING 			1
#define U_SIZE  			(size_t)256

#define PMSG(fmt,args...)               printf(fmt,##args);

#define WEB_PATH 			"./Web"		
#define DOC_NAME 			"DeviceDesc.xml"	
#define UDEVNAME 			"ToWAYetech Multimedia Player"

#define SERVICE_MUN 			3
#define UPNP_DEBUG                      1
#define MIN_LOADLEVEL 			0
#define MAX_LOADLEVEL 			100

static char *AVTransportAction[] = {
    "SetAVTransportURI",
    "SetNextAVTransportURI",
    "GetMediaInfo",
    "GetMediaInfo_Ext",
    "GetTransportInfo",
    "GetPositionInfo",
    "GetDeviceCapabilities",
    "GetTransportSettings",
    "Stop",
    "Play",
    "Pause",
    "Record",
    "Seek",
    "Next",
    "Previous",
    "SetPlayMode",
    "SetRecordQualityMode",
    "GetCurrentTransportActions",
    "GetDRMState",
    "GetStateVariables",
    "SetStateVariables"
};

static char *ConnectionManagerAction[] = {
    "GetProtocolInfo",
    "PrepareForConnection",
    "ConnectionComplete",
    "GetCurrentConnectionIDs",
    "GetCurrentConnectionInfo"
};

static char *RenderingControlAction[] = {
    "ListPresets",
    "SelectPreset",
    "GetBrightness",
    "SetBrightness",
    "GetContrast",
    "SetContrast",
    "GetSharpness",
    "SetSharpness",
    "GetRedVideoGain",
    "SetRedVideoGain",
    "GetGreenVideoGain",
    "SetGreenVideoGain",
    "GetBlueVideoGain",
    "SetBlueVideoGain",
    "GetRedVideoBlackLevel",
    "SetRedVideoBlackLevel",
    "GetGreenVideoBlackLevel",
    "SetGreenVideoBlackLevel",
    "GetBlueVideoBlackLevel",
    "SetBlueVideoBlackLevel",
    "GetColorTemperature",
    "SetColorTemperature",
    "GetHorizontalKeystone",
    "SetHorizontalKeystone",
    "GetVerticalKeystone",
    "SetVerticalKeystone",
    "GetMute",
    "SetMute",
    "GetVolume",
    "SetVolume",
    "GetVolumeDB",
    "SetVolumeDB",
    "GetVolumeDBRange",
    "GetLoudness",
    "SetLoudness",
    "GetStateVariables",
    "SetStateVariables"
};

static char *AVTransportState[] = {
    "TransportState",
    "TransportStatus",
    "CurrentMediaCategory",
    "PlaybackStorageMedium",
    "RecordStorageMedium",
    "PossiblePlaybackStorageMedia",
    "PossibleRecordStorageMedia",
    "CurrentPlayMode",
    "TransportPlaySpeed",
    "RecordMediumWriteStatus",
    "CurrentRecordQualityMode",
    "PossibleRecordQualityModes",
    "NumberOfTracks",
    "CurrentTrack",
    "CurrentTrackDuration",
    "CurrentMediaDuration",
    "CurrentTrackMetaData",
    "CurrentTrackURI",
    "AVTransportURI",
    "AVTransportURIMetaData",
    "NextAVTransportURI",
    "NextAVTransportURIMetaData",
    "RelativeTimePosition",
    "AbsoluteTimePosition",
    "RelativeCounterPosition",
    "AbsoluteCounterPosition",
    "CurrentTransportActions",
    "LastChange",
    "DRMState",
    "A_ARG_TYPE_SeekMode",
    "A_ARG_TYPE_SeekTarget",
    "A_ARG_TYPE_InstanceID",
    "A_ARG_TYPE_DeviceUDN",
    "A_ARG_TYPE_ServiceType",
    "A_ARG_TYPE_ServiceID",
    "A_ARG_TYPE_StateVariableValuePairs",
    "A_ARG_TYPE_StateVariableList"
};

static char *ConnectionManagerState[] = {
    "SourceProtocolInfo",
    "SinkProtocolInfo",
    "CurrentConnectionIDs",
    "A_ARG_TYPE_ConnectionStatus",
    "A_ARG_TYPE_ConnectionManager",
    "A_ARG_TYPE_Direction",
    "A_ARG_TYPE_ProtocolInfo",
    "A_ARG_TYPE_ConnectionID",
    "A_ARG_TYPE_AVTransportID",
    "A_ARG_TYPE_RcsID"
};

static char *RenderingControlState[] = {
    "LastChange",
    "PresetNameList",
    "Brightness",
    "Contrast",
    "Sharpness",
    "RedVideoGain",
    "GreenVideoGain",
    "BlueVideoGain",
    "RedVideoBlackLevel",
    "GreenVideoBlackLevel",
    "BlueVideoBlackLevel",
    "ColorTemperature",
    "HorizontalKeystone",
    "VerticalKeystone",
    "Mute",
    "Volume",
    "VolumeDB",
    "Loudness",
    "A_ARG_TYPE_Channel",
    "A_ARG_TYPE_InstanceID",
    "A_ARG_TYPE_PresetName",
    "A_ARG_TYPE_DeviceUDN",
    "A_ARG_TYPE_ServiceType",
    "A_ARG_TYPE_ServiceID",
    "A_ARG_TYPE_StateVariableValuePairs",
    "A_ARG_TYPE_StateVariableList"
};


enum {
    TransportState,
    TransportStatus,
    CurrentMediaCategory,
    PlaybackStorageMedium,
    RecordStorageMedium,
    PossiblePlaybackStorageMedia,
    PossibleRecordStorageMedia,
    CurrentPlayMode,
    TransportPlaySpeed,
    RecordMediumWriteStatus,
    CurrentRecordQualityMode,
    PossibleRecordQualityModes,
    NumberOfTracks,
    CurrentTrack,
    CurrentTrackDuration,
    CurrentMediaDuration,
    CurrentTrackMetaData,
    CurrentTrackURI,
    AVTransportURI,
    AVTransportURIMetaData,
    NextAVTransportURI,
    NextAVTransportURIMetaData,
    RelativeTimePosition,
    AbsoluteTimePosition,
    RelativeCounterPosition,
    AbsoluteCounterPosition,
    CurrentTransportActions,
    LastChange,
    DRMState,
    A_ARG_TYPE_SeekMode,
    A_ARG_TYPE_SeekTarget,
    A_ARG_TYPE_InstanceID,
    A_ARG_TYPE_DeviceUDN,
    A_ARG_TYPE_ServiceType,
    A_ARG_TYPE_ServiceID,
    A_ARG_TYPE_StateVariableValuePairs,
    A_ARG_TYPE_StateVariableList
} AVTRANSPORT;

enum {
    SourceProtocolInfo,
    SinkProtocolInfo,
    CurrentConnectionIDs,
    A_ARG_TYPE_ConnectionStatus,
    A_ARG_TYPE_ConnectionManager,
    A_ARG_TYPE_Direction,
    A_ARG_TYPE_ProtocolInfo,
    A_ARG_TYPE_ConnectionID,
    A_ARG_TYPE_AVTransportID,
    A_ARG_TYPE_RcsID
} CONNECTIONMANAGER;

enum {
    RLastChange,
    PresetNameList,
    Brightness,
    Contrast,
    Sharpness,
    RedVideoGain,
    GreenVideoGain,
    BlueVideoGain,
    RedVideoBlackLevel,
    GreenVideoBlackLevel,
    BlueVideoBlackLevel,
    ColorTemperature,
    HorizontalKeystone,
    VerticalKeystone,
    Mute,
    Volume,
    VolumeDB,
    Loudness,
    RA_ARG_TYPE_Channel,
    RA_ARG_TYPE_InstanceID,
    RA_ARG_TYPE_PresetName,
    RA_ARG_TYPE_DeviceUDN,
    RA_ARG_TYPE_ServiceType,
    RA_ARG_TYPE_ServiceID,
    RA_ARG_TYPE_StateVariableValuePairs,
    RA_ARG_TYPE_StateVariableList
} RENDERINGCONTROL;

static char *AVTransportVal[] = {
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
} ;

static char *ConnectionManagerVal[] = {
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
};

static char *RenderingControlVal[] = {
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
};

static int TablesMun[SERVICE_MUN*3] = {
    21, 		//SwitchPowerAction
    37, 		//SwitchPower Service State
    5, 			//DimmingAction
    10,			//Dimming Service State
    37,
    26
};

typedef int (*upnp_action)(IXML_Document *request,IXML_Document **out,const char **errorString,int Ser_Id,int pos);

static const char DeviceType[] = "urn:schemas-upnp-org:service:RenderingControl:1";

static char *ServiceType[] = {
    "urn:schemas-upnp-org:service:AVTransport:1",
    "urn:schemas-upnp-org:service:ConnectionManager:1",
    "urn:schemas-upnp-org:service:RenderingControl:1",
};

static char *ServiceTypeId[] = {
    "urn:upnp-org:serviceId:AVTransport.1",
    "urn:upnp-org:serviceId:ConnectionManager.1",
    "urn:upnp-org:serviceId:RenderingControl.1",
};

struct _State
{
    const char *Name[0];
};

struct _Action
{
    const char *Name[0];
};

struct _Defval
{
    const char *Val[0];
};

struct _Actions
{
    upnp_action *Exec[0];
};

struct _Service
{
    char UDN[NAME_SIZE];
    char Type[NAME_SIZE];
    char Id[NAME_SIZE];
    int StateCount;
    int DefvalCount;
    int ActionCount;
    int ActionsCount;
    struct _State *State;
    struct _Defval *Defval;
    struct _Action *Action;
    struct _Actions *Actions;
};


UpnpClient_Handle pt_handle;

#endif //__STRUCT_H__
