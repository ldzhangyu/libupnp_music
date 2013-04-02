/*
* _COPYRIGHT_
*
* File Name: Main.c
* System Environment: GNU/Linux
* Created Time: 2013-01-18
* Author: Johan
* E-mail: Johaness@qq.com
* Description: 
*
*/

#include "Common.h"

int main(int argc, char **argv)
{
    GMainLoop *loop;
    loop = g_main_loop_new(NULL,FALSE);
    g_type_init();
    gst_init(&argc, &argv);
    Core_init();
	Core_set_uri("file:////opt/gstreamer/old_Media/a.mp3");
    Init_Upnp();
    g_main_loop_run(loop);
    Stop_Upnp();
    Core_exit();
    return 0;
}
