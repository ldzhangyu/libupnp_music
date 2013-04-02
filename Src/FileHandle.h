/*
* _COPYRIGHT_
*
* File Name:FileHandle.h
* System Environment: GNU/Linux
* Created Time:2012-11-16
* Author: Johan
* E-mail: Johaness@qq.com
* Description: 
*
*/

#ifndef __FILEHANDLE_H__
#define __FILEHANDLE_H__

#include "Struct.h"

static int WriteFile(const char *Path,const char *Buf);
static void UpdtaeValue(const char *Path,const char *NodeElement,char *NewValue);
void ModifyXmlNodeValue(const char *NodeElement,char *NewValue);
void ModifyConFValue(const char *NodeElement,char *NewValue);
char *ReadElement(const char *Path,const char *NodeElement);
#endif //__FILEHANDLE_H__
