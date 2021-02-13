#include "IWin32_NotifyIcon.h"

#include "misc/framework.h"
#include <strsafe.h>

#include <shellapi.h>
#include <memory>

// Use a guid to uniquely identify our icon
#if SYSAPI_UWP
class __declspec(uuid("E0D07180-1F85-4EA7-80AC-E179D75D1FB8")) PowerTipIcon;
#else

#ifdef NDEBUG
class __declspec(uuid("FF7F5401-B49E-4819-9D7E-E3540085900F")) PowerTipIcon;
#else
class __declspec(uuid("881DE7D9-4219-41B8-8E17-8EB1D8F897FD")) PowerTipIcon;
#endif

#endif

#define IconResourceId m_resourceId

IWin32_NotifyIcon::IWin32_NotifyIcon(HWND parent, DWORD resId) : IWin32Object(parent, resId)
{
    // do nothing.
}

IWin32_NotifyIcon::~IWin32_NotifyIcon()
{
    hide();
}

void IWin32_NotifyIcon::showToast(std::string title, std::string body, ENotifyIcon ni)
{
    NOTIFYICONDATA nid2 = {sizeof(nid2)};
    nid2.uFlags = NIF_INFO | NIF_GUID;
    nid2.guidItem = __uuidof(PowerTipIcon);

    switch (ni)
    {
    case ENotifyIcon::kNotifyIconApplication:
        nid2.dwInfoFlags = NIIF_USER | NIIF_LARGE_ICON;
        LoadIconMetric(GetModuleHandle(0), MAKEINTRESOURCEW(IconResourceId), LIM_LARGE, &nid2.hBalloonIcon);
        break;

    case ENotifyIcon::kNotifyIconCritical:
        nid2.dwInfoFlags = NIIF_ERROR;
        break;

    case ENotifyIcon::kNotifyIconExclamation:
        nid2.dwInfoFlags = NIF_MESSAGE;
        break;

    case ENotifyIcon::kNotifyIconInformation:
        nid2.dwInfoFlags = NIF_INFO;
        break;

    case ENotifyIcon::kNotifyIconNone:
        nid2.dwInfoFlags = 0;
        break;
    }

    strcpy(nid2.szInfoTitle, title.c_str());
    strcpy(nid2.szInfo, body.c_str());

    Shell_NotifyIcon(NIM_MODIFY, &nid2);
}

bool IWin32_NotifyIcon::show()
{
    NOTIFYICONDATA nid = {sizeof(nid)};
    nid.hWnd = getHandle();
    // add the icon, setting the icon, tooltip, and callback message.
    // the icon will be identified with the GUID
    nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE | NIF_SHOWTIP | NIF_GUID;
    nid.guidItem = __uuidof(PowerTipIcon);
    nid.uCallbackMessage = WMAPP_NOTIFYCALLBACK;
    LoadIconMetric(GetModuleHandle(0), MAKEINTRESOURCEW(IconResourceId), LIM_SMALL, &nid.hIcon);
    
    StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), "PowerTip");
    Shell_NotifyIcon(NIM_ADD, &nid);

    // NOTIFYICON_VERSION_4 is prefered
    nid.uVersion = NOTIFYICON_VERSION_4;
    return Shell_NotifyIcon(NIM_SETVERSION, &nid);
}

void IWin32_NotifyIcon::hide()
{
    // Shell_NotifyIcon(NIM_DELETE, &nid);
}

void IWin32_NotifyIcon::setContextMenu(DWORD menuResId, int pos)
{
    hMenuResId = menuResId;
    m_pos = pos;
}

void IWin32_NotifyIcon::showContextMenu()
{
    setContextMenu(hMenuResId, m_pos);

    hMenu = LoadMenu(NULL, MAKEINTRESOURCE(hMenuResId));

    if (m_pos > -1)
    {
        hMenu = GetSubMenu(hMenu, m_pos);
    }

    if (hMenu)
    {
        POINT pt;
        GetCursorPos(&pt);
        SetForegroundWindow(getHandle());
        TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, getHandle(), NULL);
        PostMessage(getHandle(), WM_NULL, 0, 0);
        DestroyMenu(hMenu);
    }
}

void IWin32_NotifyIcon::hideContextMenu()
{

}

BOOL IWin32_NotifyIcon::RestoreTooltip()
{
	// After the balloon is dismissed, restore the tooltip.
	NOTIFYICONDATA nid = {sizeof(nid)};
	nid.uFlags = NIF_SHOWTIP | NIF_GUID;
	nid.guidItem = __uuidof(PowerTipIcon);
	return Shell_NotifyIcon(NIM_MODIFY, &nid);
}