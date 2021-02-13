#pragma once

#include "IWin32Object.h"
#include "IResizableControl.h"
#include "IControl.h"

#define IButton IWin32_Button

class IWin32_Button : public IControl, public IWin32Object, IResizableControl {
public:
	IWin32_Button(HWND window, DWORD resId);
	virtual ~IWin32_Button();

	void setFont(int size, const char* fontName);
	void setText(const char* text);

	void setEnabled(bool enabled);
	void show();
	void hide();

	// Inherited via IResizableControl
	virtual void setSize(int width, int height) override;
	virtual void setLocation(int x, int y) override;
};