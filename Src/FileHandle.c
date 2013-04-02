/*
 * _COPYRIGHT_
 *
 * File Name: FileHandle.c
 * System Environment: GNU/Linux
 * Created Time: 2012-11-16
 * Author: Johan
 * E-mail: Johaness@qq.com
 * Description: 
 *
 */

#include "FileHandle.h"

static int WriteFile(const char *Path,const char *Buf)
{
	FILE *fd;
	int size = 0;

	if((fd = fopen(Path,"w+")) == NULL)
		return ERROR;

	size = strlen(Buf);

	if(size != fwrite(Buf,1,size,fd))
	{
		fclose(fd);
		return ERROR;
	}

	fclose(fd);

	return SUCCESS;
}

//path,  friendlyName
static void UpdateValue(const char *Path,const char *NodeElement, char *NewValue)
{
	char *Buf = NULL;

	IXML_Document *doc = NULL;
	IXML_NodeList *node = NULL;
	IXML_Node *NodePtr = NULL;

	if(ixmlLoadDocumentEx(Path, &doc) == IXML_INVALID_PARAMETER)
		goto EXIT_THIS;

	node = ixmlDocument_getElementsByTagName(doc, NodeElement);

	if (node) 
	{
		if (NodePtr = ixmlNodeList_item(node, 0)) 
		{
			NodePtr = ixmlNode_getFirstChild(NodePtr);
			ixmlNode_setNodeValue(NodePtr,NewValue);
		} 
	}
	else
	{
		goto EXIT_XML;
	}

	Buf = ixmlPrintDocument(doc);

	if(WriteFile(Path,Buf) != SUCCESS)
		goto EXIT_THIS;

EXIT_XML:
	if (node)
		ixmlNodeList_free(node);
	free(Buf);
	ixmlDocument_free(doc);  
EXIT_THIS:
	return;
}

//
void ModifyXmlNodeValue(const char *NodeElement,char *NewValue)
{

	char *Value = NULL;
	char *Path = NULL;

	Value = malloc(sizeof(char) * (strlen(UDEVNAME) + strlen(NewValue) + 4));
	Path = malloc(sizeof(char) * (strlen(WEB_PATH) + strlen(DOC_NAME) + 2));
	memset(Path,0,sizeof(Path));
	memset(Value,0,sizeof(Value));

	strcpy(Value,UDEVNAME);
	strcat(Value,"(");
	strcat(Value,NewValue);//ip_address
	strcat(Value,")");

	strcpy(Path,WEB_PATH);
	strcat(Path,"/");
	strcat(Path,DOC_NAME);

	//path,  friendlyName
	UpdateValue(Path,NodeElement,Value);

	free(Path);
	Path = NULL;
	free(Value);
	Value = NULL;

	return;
}

void ModifyConFValue(const char *NodeElement,char *NewValue)
{
#if 0
	char *Path = NULL;

	Path = malloc(sizeof(char) * (strlen(CONFDIR) + strlen(CONFFILE) + 2));
	memset(Path,0,sizeof(Path));
	strcpy(Path,CONFDIR);
	strcat(Path,"/");
	strcat(Path,CONFFILE);

	UpdateValue(Path,NodeElement,NewValue);

	free(Path);
	Path = NULL;
#endif
	return;
}

char *ReadElement(const char *Path,const char *NodeElement)
{
	char *Val = NULL;
	IXML_Document *doc = NULL;
	IXML_NodeList *node = NULL;
	IXML_Node *NodePtr = NULL;

	if(ixmlLoadDocumentEx(Path, &doc) == IXML_INVALID_PARAMETER)
		goto EXIT_THIS;

	node = ixmlDocument_getElementsByTagName(doc, NodeElement);

	if (node) 
	{
		if (NodePtr = ixmlNodeList_item(node, 0)) 
		{
			NodePtr = ixmlNode_getFirstChild(NodePtr);
			if(!NodePtr)
			{
				Val = (NULL);
			}
			Val = NodePtr->nodeValue;//strdup(NodePtr->nodeValue);
			if(!Val)
			{
				Val = (NULL);
			}
		} 
	}

	if (node)
		ixmlNodeList_free(node);
	ixmlDocument_free(doc);  
EXIT_THIS:
	return Val;
}

