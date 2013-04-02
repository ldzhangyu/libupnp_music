/*
 * _COPYRIGHT_
 *
 * File Name: core.c
 * System Environment: GNU/Linux
 * Created Time: 2013-01-14
 * Author: Johan
 * E-mail: Johaness@qq.com
 * Description: 
 *
 */

#include "Core.h"

const char *This_Module = "Core";  
static CoreData Core;

void Core_init(void)
{
	static gboolean init = FALSE;
	if(init) return;
	init = TRUE;
	GstBus *bus;
	GstElement *seff = NULL;
	GstElement *play = NULL;
	GstElement *audio_sink = NULL;
	GstElement *video_fakesink = NULL;
	GstElement *audio_equalizer = NULL;
	GstElement *audio_convert = NULL;
	GstElement *volume_plugin = NULL;

	GstPad *pad;
	gdouble volume = 1.0;
	gboolean flag = FALSE;
	GError *error = NULL;

	Modle_Debug_Printf(This_Module, "Loading...");

	flag = Core_Gst_Plugin_Check();

	if(!flag)
	{
		Modle_Debug_Perror(This_Module,"Effect plugins are missing!" "missing, effects are not available now!");
	}

	play = gst_element_factory_make("playbin2", "play");      

	if(play == NULL)
	{
		play = gst_element_factory_make("playbin","play");
	}

	if(!GST_IS_ELEMENT(play)) 
	{
		Modle_Debug_Printf(This_Module,"Failed to make playbin element!");
		exit(2);
	}

	if(flag)
	{
		audio_sink = gst_element_factory_make("autoaudiosink", "audio_sink");
		video_fakesink = gst_element_factory_make("fakesink", "video_sink");
		audio_equalizer = gst_element_factory_make("equalizer-10bands", "audio_equalizer");
		audio_convert = gst_element_factory_make("audioconvert", "eqauconv");
		volume_plugin = gst_element_factory_make("volume", "volume_plugin");

		if(!GST_IS_ELEMENT(audio_equalizer) || !GST_IS_ELEMENT(audio_sink) || !GST_IS_ELEMENT(audio_convert) || !GST_IS_ELEMENT(volume_plugin))
		{
			flag = FALSE;

			if(GST_IS_ELEMENT(audio_equalizer))
				gst_object_unref(audio_equalizer);
			if(GST_IS_ELEMENT(audio_sink))
				gst_object_unref(audio_sink);
			if(GST_IS_ELEMENT(audio_convert))
				gst_object_unref(audio_convert);
			if(GST_IS_ELEMENT(volume_plugin))
				gst_object_unref(volume_plugin);
		}

	}

	if(GST_IS_ELEMENT(video_fakesink)) 
	{
		g_object_set(G_OBJECT(video_fakesink),"sync",TRUE,NULL);
		g_object_set(G_OBJECT(play),"video_sink",video_fakesink,NULL);
	}

	if(flag)
	{
		seff = gst_bin_new("audio_bin");
		gst_bin_add_many(GST_BIN(seff),audio_convert,audio_equalizer,volume_plugin,audio_sink,NULL);

		if(!gst_element_link_many(audio_convert,audio_equalizer,volume_plugin,audio_sink,NULL))
		{
			flag = FALSE;
			Modle_Debug_Perror(This_Module,"Can't Link Elements," "effects are not available now!");

			if(GST_IS_ELEMENT(audio_equalizer))
			{
				gst_object_unref(audio_equalizer);
			}

			if(GST_IS_ELEMENT(audio_sink))
			{
				gst_object_unref(audio_sink);
			}

			if(GST_IS_ELEMENT(audio_convert))
			{
				gst_object_unref(audio_convert);
			}

			if(GST_IS_ELEMENT(volume_plugin))
			{
				gst_object_unref(volume_plugin);
			}

			if(GST_IS_ELEMENT(seff))
			{
				gst_object_unref(seff);
			}
		}
	}

	if(flag)
	{
		pad = gst_element_get_static_pad(audio_convert, "sink");
		gst_element_add_pad(seff, gst_ghost_pad_new(NULL, pad));
		gst_object_unref(pad);
		g_object_set(G_OBJECT(play), "audio-sink", seff, NULL);

		pad = gst_element_get_static_pad(audio_convert, "src");
		gst_pad_add_buffer_probe(pad, G_CALLBACK(Core_pad_buffer_probe), NULL);
		gst_object_unref(pad);

		Core.Element.Equal = audio_convert;
		Core.Element.Volume = volume_plugin;

		Core.Full_mode = TRUE;

		Modle_Debug_Printf(This_Module, "Full mode enabled.");
	}
	else
	{
		Modle_Debug_Printf(This_Module, "Safe mode enabled.");
	}

	bus = gst_pipeline_get_bus(GST_PIPELINE(play));
	gst_bus_add_watch(bus, (GstBusFunc)Core_bus_call, &Core);
	gst_object_unref(bus);
	gst_element_set_state(play, GST_STATE_NULL);

	Core.Element.Playbin = play;
	Core_set_volume(volume * 100);

	gst_element_set_state(play, GST_STATE_READY);

	gst_version(&Core.Version.Major, &Core.Version.Minor, &Core.Version.Micro, &Core.Version.Nano);

	Modle_Debug_Printf(This_Module, "Loaded successfully The Multimedia(GS) Support Version %d.%d.%d.%d",Core.Version.Major, Core.Version.Minor, Core.Version.Micro, Core.Version.Nano);

	return;

}

void Core_exit(void)
{
	Modle_Debug_Printf(This_Module,"Exit...");
}

static gboolean Core_Gst_Plugin_Check(void)
{
	if(gst_default_registry_check_feature_version("playbin2", 0, 10, 0))
	{
		Modle_Debug_Printf(This_Module, "Check playbin... OK!");
	}
	else
	{
		if(gst_default_registry_check_feature_version("playbin", 0, 10, 0)) 
		{
			Modle_Debug_Printf(This_Module, "Check playbin... OK!");
		}
		else
		{
			Modle_Debug_Printf(This_Module, "Check playbin... Not found!");
			return FALSE;
		}
	}

	if(gst_default_registry_check_feature_version("decodebin2", 0, 10, 0))
	{
		Modle_Debug_Printf(This_Module, "Check decodebin... OK!");
	}
	else
	{
		if(gst_default_registry_check_feature_version("decodebin", 0, 10, 0))       
		{
			Modle_Debug_Printf(This_Module, "Check decodebin... OK!");
		}
		else
		{
			Modle_Debug_Printf(This_Module, "Check decodebin... Not found!");
			return FALSE;
		}
	}

	if(gst_default_registry_check_feature_version("fakesink", 0, 10, 0))
	{
		Modle_Debug_Printf(This_Module, "Check fakesink... OK!");
	}
	else
	{
		Modle_Debug_Printf(This_Module, "Check fakesink... Not found!");
		return FALSE;
	}

	if(gst_default_registry_check_feature_version("autoaudiosink", 0, 10, 0))
	{
		Modle_Debug_Printf(This_Module, "Check autoaudiosink... OK!");
	}
	else
	{
		Modle_Debug_Printf(This_Module, "Check autoaudiosink... " "Not found!");
		return FALSE;
	}

	if(gst_default_registry_check_feature_version("equalizer-10bands", 0, 10,0))
	{
		Modle_Debug_Printf(This_Module, "Check equalizer-10bands... OK!");
	}
	else
	{
		Modle_Debug_Printf(This_Module, "Check equalizer-10bands... " "Not found!");
		return FALSE;
	}

	if(gst_default_registry_check_feature_version("volume", 0, 10, 0))
	{
		Modle_Debug_Printf(This_Module, "Check volume... OK!");
	}
	else
	{
		Modle_Debug_Printf(This_Module, "Check volume... Not found!");
		return FALSE;
	}

	if(gst_default_registry_check_feature_version("audioconvert", 0, 10, 0))
	{
		Modle_Debug_Printf(This_Module, "Check audioconvert... OK!");
	}
	else
	{
		Modle_Debug_Printf(This_Module, "Check audioconvert... Not found!");
		return FALSE;
	}

	return TRUE;
}

static gboolean Core_bus_call(GstBus *bus, GstMessage *msg, gpointer data)
{
	gchar *debug;
	GstState state, pending;
	gchar *plugin_error_msg;
	GError *error;
	switch(GST_MESSAGE_TYPE(msg))
	{
		case GST_MESSAGE_EOS:
			Modle_Debug_Printf(This_Module, "Reached EOS, playing the next one.");
			Core_stop();
			break;
		case GST_MESSAGE_SEGMENT_DONE:
			Modle_Debug_Printf(This_Module, "Segment is done.");
			break;
		case GST_MESSAGE_STATE_CHANGED:
			gst_message_parse_state_changed(msg, NULL, &state, &pending);

			if(pending!=GST_STATE_VOID_PENDING) break;

			switch(state)
			{
				case GST_STATE_PLAYING:
					break;
				case GST_STATE_PAUSED:
					break;
				default:
					break;
			}
			Core.State = state;
			break;
		case GST_MESSAGE_ERROR:
			gst_message_parse_error(msg, &error, &debug);
			Modle_Debug_Perror(This_Module, "%s\nDEBUG: %s", error->message, debug);
			g_error_free(error);
			g_free(debug);
			Modle_Debug_Perror(This_Module, "Error occured, sending " "EOS message...");
			if(!gst_element_post_message(Core.Element.Playbin,gst_message_new_eos(GST_OBJECT(Core.Element.Playbin))))
			{
				Core_stop();
			}
			break;
		case GST_MESSAGE_TAG:
			break;
		case GST_MESSAGE_BUFFERING:
			break;
		case GST_MESSAGE_DURATION:
			break;
		case GST_MESSAGE_NEW_CLOCK:
			Modle_Debug_Printf(This_Module, "Get a new clock.");

			if(Core.Start_time>0)
			{
				Modle_Debug_Printf(This_Module, "Starting a segment playing.");
				gst_element_seek_simple(Core.Element.Playbin, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE,Core.Start_time);
			}
			break;

		default:
			break;
	}
	return TRUE;
}

static gboolean Core_pad_buffer_probe(GstPad *pad, GstBuffer *buf, gpointer data)
{
	GstMessage *msg;

	gint64 pos = (gint64)GST_BUFFER_TIMESTAMP(buf);
	gint64 len = Core_get_Music_length();

	if(Core.End_time > 0)
	{
		if(Core.End_time < pos)
		{
			msg = gst_message_new_eos(GST_OBJECT(Core.Element.Playbin));
			Modle_Debug_Printf(This_Module, "Reached the end time in " "segment playing, sending a new EOS event now.");
			if(!gst_element_post_message(Core.Element.Playbin, msg))
			{
				Core_stop();
			}
		}
	}
	else if(len > 0 && pos-len > 2*GST_SECOND)
	{
		msg = gst_message_new_eos(GST_OBJECT(Core.Element.Playbin));
		Modle_Debug_Printf(This_Module, "Reached the end time in normal " "playing, sending a new EOS event now.");

		if(!gst_element_post_message(Core.Element.Playbin, msg))
		{
			Core_stop();   
		}
	}
	return TRUE;
}

gint64 Core_get_Music_length()
{
	gint64 dura = 0;
	GstFormat fmt = GST_FORMAT_TIME;

	if(Core.Start_time >= 0 && Core.End_time > 0)
	{
		dura = Core.End_time - Core.Start_time;
		if(dura>0) return dura;
	}

	if(gst_element_query_duration(Core.Element.Playbin, &fmt, &dura))
	{
		if(dura<0) dura = 0;
	}

	if(Core.Start_time > 0 && dura - Core.Start_time > 0)
	{

		dura = dura - Core.Start_time;
	}

	return dura;
}

void Core_set_uri(const gchar *uri)
{
	g_object_set(G_OBJECT(Core.Element.Playbin), "uri", uri, NULL);
}

gboolean Core_play(void)
{
	GstState state;
	gboolean flag = TRUE;

	gst_element_get_state(GST_ELEMENT(Core.Element.Playbin), &state, NULL, GST_CLOCK_TIME_NONE);

	if(state != GST_STATE_PAUSED && state != GST_STATE_PLAYING && state != GST_STATE_READY && state != GST_STATE_NULL)
	{
		flag = gst_element_set_state(GST_ELEMENT(Core.Element.Playbin), GST_STATE_NULL);

		if(!flag) 
		{
			return FALSE;
		}
	}

	flag = gst_element_set_state(GST_ELEMENT(Core.Element.Playbin), GST_STATE_PLAYING);

	if(!flag) 
	{
		return FALSE;
	}

	if(state == GST_STATE_PAUSED)
	{
	}
	else
	{
	}

	Modle_Debug_Printf(This_Module, "Start playing...");

	return TRUE;
}

gboolean Core_stop(void)
{
	GstState state;

	gboolean flag = TRUE;

	flag = gst_element_set_state(GST_ELEMENT(Core.Element.Playbin), GST_STATE_NULL);

	if(!flag) 
	{
		Modle_Debug_Printf(This_Module, "can't Stop playing...");
		return FALSE;
	}

	Modle_Debug_Printf(This_Module, "Stop playing...");

	return TRUE;
}

gboolean Core_pause(void)
{
	gboolean flag = TRUE;
	gint64 pos = Core_get_play_position();
	flag = gst_element_set_state(Core.Element.Playbin, GST_STATE_PAUSED);
	if(pos > 0) 
		Core_set_play_position(pos);
	if(!flag) 
		return FALSE;

	Modle_Debug_Printf(This_Module, "Trying to pause...");
	return TRUE;
}

gint64 Core_get_play_position()
{
	gint64 pos = 0;
	GstFormat fmt = GST_FORMAT_TIME;

	if(gst_element_query_position(Core.Element.Playbin, &fmt, &pos))
	{
		if(pos < 0) 
			pos = 0;
	}

	if(Core.Start_time > 0 && pos - Core.Start_time > 0)
		pos = pos - Core.Start_time;
	return pos;
}

gboolean Core_set_play_position(gint64 time)
{ 
	if(time<0) return FALSE;
	if(Core.Start_time > 0)
	{
		gst_element_seek_simple(Core.Element.Playbin, GST_FORMAT_TIME,GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE,time + Core.Start_time);
	}
	else
	{
		gst_element_seek_simple(Core.Element.Playbin, GST_FORMAT_TIME,GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE, time);
	}
	return TRUE;
}

gdouble Core_get_volume()
{
	gdouble volume;

	if(Core.Element.Volume != NULL)
		g_object_get(Core.Element.Volume, "volume", &volume, NULL);
	else
		g_object_get(Core.Element.Playbin, "volume", &volume, NULL);
	return volume * 100;
}

gboolean Core_set_volume(gdouble volume)
{
	volume /= 100;
	if(Core.Element.Volume != NULL)
		g_object_set(G_OBJECT(Core.Element.Volume), "volume", volume, NULL);
	else
		g_object_set(G_OBJECT(Core.Element.Playbin), "volume", volume, NULL);
	return TRUE;
}

