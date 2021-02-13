#pragma once

#include "IWin32Object.h"
#include "IResizableControl.h"
#include "IControl.h"

#define ICheckBox IWin32_CheckBox

class IWin32_CheckBox : public IControl, public IWin32Object, IResizableControl {
public:
	IWin32_CheckBox(HWND window, DWORD resId);
	virtual ~IWin32_CheckBox();

	void setFont(int size, const char* fontName);
	void setText(const char* text);

	void setChecked();
	void setUnchecked();

	bool isChecked();

	void setEnabled(bool enabled);
	void show();
	void hide();

	// Inherited via IResizableControl
	virtual void setSize(int width, int height) override;
	virtual void setLocation(int x, int y) override;
};