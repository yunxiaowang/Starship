// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include "Resource.h"

#include "odPrintf.h"

#ifndef FAST_DELETE
#define FAST_DELETE(x) if( x ) { delete(x); (x) = NULL; }
#endif

#ifndef FAST_DELETE_ARRAY
#define FAST_DELETE_ARRAY(x) if( x ) { delete [] (x); (x) = NULL; }
#endif

#ifndef FAST_RELEASE			
#define FAST_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif

//#ifndef MSGOUTPUT
//#define MSGOUTPUT(s) { char buf[1024]; sprintf_s(buf, "%s");
//MessageBoxA(0, buf, "Error", 0);


// TODO: reference additional headers your program requires here
