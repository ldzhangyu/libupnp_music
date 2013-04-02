/*
* _COPYRIGHT_
*
* File Name: debug.c
* System Environment: GNU/Linux
* Created Time: 2013-01-14
* Author: Johan
* E-mail: Johaness@qq.com
* Description: 
*
*/

#include "Debug.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>

int Debug_Flag = DEBUG_MODE; 

int Get_Debug_Flag(void)
{
    return Debug_Flag;
}

int Set_Debug_Flag(int Mode)
{
    Debug_Flag = Mode;
    return 0;
}

int Debug_Printf(const char *format, ...)
{
    int result;
    va_list arg_ptr;

    va_start(arg_ptr, format);

    if(!Debug_Flag) 
	return 0;

    result = vprintf(format, arg_ptr);

    return result;
}

int Debug_Perror(const char *format, ...)
{
    int result;
    va_list arg_ptr;

    va_start(arg_ptr, format);

    result = vfprintf(stderr, format, arg_ptr);

    return result;
}

int Modle_Debug_Printf(const char *module_name, const char *format, ...)
{
    int result;
    char *tmp = "%s: %s\n";
    char *new_format;
    va_list arg_ptr;

    va_start(arg_ptr, format);

    new_format = (char *)malloc(strlen(tmp) + strlen(module_name) + strlen(format));

    sprintf(new_format,tmp,module_name, format);

    result = vfprintf(stdout, new_format, arg_ptr);

    free(new_format);

    return result;
}

int Modle_Debug_Perror(const char *module_name, const char *format, ...)
{
    int result;
    char *tmp = "%s-ERROR: %s\n";
    char *new_format;
    va_list arg_ptr;

    va_start(arg_ptr, format);

    new_format = (char *)malloc(strlen(tmp) + strlen(module_name) + strlen(format));

    sprintf(new_format,tmp,module_name, format);


    result = vfprintf(stderr, new_format, arg_ptr);

    free(new_format);

    return result;
}
