#pragma once

#include "IWin32Object.h"
#include <string>
#include <functional>

#define INotifyIcon IWin32_NotifyIcon

UINT const WMAPP_NOTIFYCALLBACK = WM_APP + 1;
UINT const WMAPP_HIDEFLYOUT     = WM_APP + 2;

enum class ENotifyIcon
{
    kNotifyIconExclamation,
    kNotifyIconCritical,
    kNotifyIconInformation,
    kNotifyIconNone,
    kNotifyIconApplication
};

class IWin32_NotifyIcon : public IWin32Object
{
public:
    IWin32_NotifyIcon(HWND parent, DWORD resId);
    virtual ~IWin32_NotifyIcon();

    void showToast(std::string title, std::string body, ENotifyIcon ni = ENotifyIcon::kNotifyIconApplication);
    bool show();
    void hide();
    void setContextMenu(DWORD menuResId, int pos = -1); /* -1 implies default */
    void showContextMenu();
    void hideContextMenu();

    // Win32-specific code

    BOOL RestoreTooltip();

private:
    HMENU hMenu;
    DWORD hMenuResId;
    HICON hIcon;
    int m_pos;
};