// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <CommCtrl.h>


#define MAX_LOADSTRING 100

#define INITIALX_96DPI 50 
#define INITIALY_96DPI 50 
#define INITIALWIDTH_96DPI 100 
#define INITIALHEIGHT_96DPI 50 

#define CLASS_DATA(clazz, hWnd) reinterpret_cast<clazz*>(GetWindowLongPtr(hWnd, GWLP_USERDATA))

static 
void 
ChangeFont(HWND hDlg, int resId, int size, const char* name)
{
	HFONT hFont = CreateFont(size, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, name);
	SendMessage(GetDlgItem(hDlg, resId), WM_SETFONT, WPARAM(hFont), TRUE);
}