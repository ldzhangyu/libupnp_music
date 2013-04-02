/*
* _COPYRIGHT_
*
* File Name:common.h
* System Environment: GNU/Linux
* Created Time:2013-01-14
* Author: Johan
* E-mail: Johaness@qq.com
* Description: 
*
*/

#ifndef __COMMON_H__
#define __COMMON_H__

#include <glib.h>
#include <stdio.h>
#include <assert.h>
#include <gst/gst.h>
#include <glib/gi18n.h>
#include "Debug.h"

struct Gst_element
{
    GstElement *Playbin;
    GstElement *Audio_sink;
    GstElement *Equal;
    GstElement *Convert;
    GstElement *Volume;
};

struct Gst_Version
{
    int Major;
    int Minor;
    int Micro;
    int Nano;
};

typedef struct CoreData {
    struct Gst_element Element;
    gint64 Start_time;
    gint64 End_time;
    gboolean Full_mode;
    GstState State;
    struct Gst_Version Version;
}CoreData;

#define VERSION 			"0.0.1"
#endif //__COMMON_H__
