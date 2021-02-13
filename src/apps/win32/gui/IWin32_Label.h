#pragma once

#include "IWin32Object.h"
#include "IResizableControl.h"
#include "IControl.h"

#define ILabel IWin32_Label

class IWin32_Label : public IControl, public IWin32Object, public IResizableControl {
public:
	IWin32_Label(HWND window, DWORD resId);
	virtual ~IWin32_Label();

	void setFont(int size, const char* fontName);
	void setText(const char* text);

	void setEnabled(bool enabled);
	void show();
	void hide();

	// Inherited via IResizableControl
	void setSize(int width, int height) override;
	void setLocation(int x, int y) override;
	int getWidth();
	int getHeight();
};