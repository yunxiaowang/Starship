#include "stdafx.h"
#include <stdio.h>
#include <stdarg.h>
#include <windows.h>


#define MAX_DBG_MSG_LEN (4096)        
void odPrintfA (const char * format,...)    
{        
	char buf[MAX_DBG_MSG_LEN] = {'[','W','Y','X',']',' '};
	va_list ap;        
	va_start(ap, format);        
	_vsnprintf_s(buf + 6,sizeof(buf) - 6, sizeof(buf) - 6, format, ap);        
	va_end(ap);        
	OutputDebugStringA(buf);    
}

void odPrintfW(const WCHAR * format,...)
{
	WCHAR wbuff[MAX_DBG_MSG_LEN] = {'[','W','Y','X',']',' '};
	va_list body;
	va_start(body,format);
	vswprintf_s(wbuff + 6,MAX_DBG_MSG_LEN - 6,format,body);
	va_end(body);
	OutputDebugStringW(wbuff);
}