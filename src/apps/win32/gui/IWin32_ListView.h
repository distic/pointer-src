#pragma once

#include "IWin32Object.h"
#include "IResizableControl.h"
#include "IControl.h"
#include "IWin32_ListViewItem.h"

#define IListView IWin32_ListView

class IWin32_ListView : public IControl, public IWin32Object, IResizableControl {
public:
	IWin32_ListView(HWND hList, DWORD resId);
	virtual ~IWin32_ListView();

	void addItem(IWin32_ListViewItem& lvItem);

	void setFullRowSelect();

	// Inherited via IResizableControl
	virtual void setSize(int width, int height) override;
	virtual void setLocation(int x, int y) override;
};