#include "IWin32_ComboBox.h"

IWin32_ComboBox::IWin32_ComboBox(HWND window, DWORD resId) : IWin32Object(GetDlgItem(window, resId), resId)
{
    // do nothing.
}

IWin32_ComboBox::~IWin32_ComboBox()
{
    // do nothing.
}

void IWin32_ComboBox::addItem(int id, std::string caption)
{
    SendMessage(m_hWnd,CB_ADDSTRING, id, reinterpret_cast<LPARAM>(_T(caption.c_str())));
}