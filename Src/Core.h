/*
* _COPYRIGHT_
*
* File Name:core.h
* System Environment: GNU/Linux
* Created Time:2013-01-14
* Author: Johan
* E-mail: Johaness@qq.com
* Description: 
*
*/

#ifndef __CORE_H__
#define __CORE_H__

#include <time.h>
#include "Common.h"
#include <gst/pbutils/missing-plugins.h>
#include <gst/pbutils/install-plugins.h>

/**
 * Core_init:
 *
 * Initialize the Core of the player. Can be used only once.
 *
 * @(void):NULL
**/
void Core_init(void);

/**
 * Core_exit:
 *
 * Exits the Core of the player And Free!.
 *
 * @(void):NULL
**/
void Core_exit(void);

/**
 * Core_exit:
 *
 * Check the Gst Plugins Is Available Or Unavailable.
 *
 * @(void):NULL
 *
 * Returns:Whether the Gst Plugins is Available, Return successfully.
**/
static gboolean Core_Gst_Plugin_Check(void);

static gboolean Core_bus_call(GstBus *bus, GstMessage *msg, gpointer data);
static gboolean Core_pad_buffer_probe(GstPad *pad, GstBuffer *buf, gpointer data);

gint64 Core_get_Music_length(void);

void Core_set_uri(const gchar *uri);

gboolean Core_play(void);
gboolean Core_stop(void);
gboolean Core_pause(void);
gint64 Core_get_play_position();
gboolean Core_set_play_position(gint64 time);
gdouble Core_get_volume();
gboolean Core_set_volume(gdouble volume);

#endif //__CORE_H__
