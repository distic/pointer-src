#pragma once

#include "IWin32Object.h"
#include <string>

#define IComboBox IWin32_ComboBox

class IWin32_ComboBox : public IWin32Object {
public:
	IWin32_ComboBox(HWND window, DWORD resId);
	virtual ~IWin32_ComboBox();

    void addItem(int id, std::string caption);
};