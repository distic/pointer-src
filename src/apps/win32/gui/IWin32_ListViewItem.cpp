#include "IWin32_ListViewItem.h"

IWin32_ListViewItem::IWin32_ListViewItem() : IWin32Object(0, 0)
{
	memset(&m_LvItem, 0, sizeof(m_LvItem));

	m_LvItem.mask = LVIF_TEXT;
	m_LvItem.cchTextMax = MAX_PATH;
	
	setIndex(0);
	setSubItem(0);
}

IWin32_ListViewItem::~IWin32_ListViewItem()
{
	// do nothing.
}

void 
IWin32_ListViewItem::setIndex(int i)
{
	m_LvItem.iItem = i;
}

void 
IWin32_ListViewItem::setSubItem(int i)
{
	m_LvItem.iSubItem = i;
}

void 
IWin32_ListViewItem::setText(std::string text)
{
	memset(m_text, '\0', sizeof(m_text));
	strcpy(m_text, text.c_str());
	m_LvItem.pszText = const_cast<char*>(m_text);
}

LVITEM 
IWin32_ListViewItem::getHandle() const
{
	return m_LvItem;
}