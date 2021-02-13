#pragma once

#include <string>
#include "IWin32Object.h"

#define IListViewItem IWin32_ListViewItem

class IWin32_ListViewItem : IWin32Object {
public:
	IWin32_ListViewItem();
	virtual ~IWin32_ListViewItem();

	void setIndex(int);
	void setSubItem(int);
	void setText(std::string text);

	LVITEM getHandle() const;

private:
	char m_text[255];

	LVITEM m_LvItem;
	TCHAR iItemText[MAX_PATH] = "";
	TCHAR iSubItemText[MAX_PATH] = "";
};