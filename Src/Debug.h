/*
* _COPYRIGHT_
*
* File Name:debug.h
* System Environment: GNU/Linux
* Created Time:2013-01-14
* Author: Johan
* E-mail: Johaness@qq.com
* Description: 
*
*/

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "Common.h"

#ifndef DEBUG_MODE
#define DEBUG_MODE 			FALSE
#endif

int Get_Debug_Flag(void);
int Set_Debug_Flag(int Mode);

int Debug_Printf(const char *format, ...);
int Debug_Perror(const char *format, ...);

int Modle_Debug_Printf(const char *module_name, const char *format, ...);
int Modle_Debug_Perror(const char *module_name, const char *format, ...);

#endif //__DEBUG_H__
