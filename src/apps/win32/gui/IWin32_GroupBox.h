#pragma once

#include "IResizableControl.h"
#include "IWin32Object.h"
#include "IControl.h"

#define IGroupBox IWin32_GroupBox

class IWin32_GroupBox : public IControl, public IWin32Object, IResizableControl {
public:
	IWin32_GroupBox(HWND window, DWORD resourceId);
	virtual ~IWin32_GroupBox();

	void setTitle(const char* title);

	// Inherited via IResizableControl
	virtual void setSize(int width, int height) override;
	virtual void setLocation(int x, int y) override;

};