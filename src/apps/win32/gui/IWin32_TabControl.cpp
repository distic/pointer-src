#include "IWin32_TabControl.h"

IWin32_TabControl::IWin32_TabControl(IWindow& w, DWORD resourceId) : IWin32Object(GetDlgItem(w.getHandle(), resourceId), resourceId),
m_defaultIndex(0)
{
	m_tci.mask = TCIF_TEXT;

	if (!m_hWnd)
	{
		throw "Tab Control not found!";
	}

	if (m_defaultIndex < 0)
	{
		throw "Default Tab Index is less than zero!";
	}

	invalidatePlacementParams();
	w.bindTabSel([&]() { onTabSelectionChanged(); });
}

IWin32_TabControl::~IWin32_TabControl()
{
	for (auto iTabPage : m_tabPages)
	{
		if (iTabPage != nullptr)
		{
			delete iTabPage;
			iTabPage = nullptr;
		}
	}

	DestroyWindow(m_hWnd);
}

void 
IWin32_TabControl::setDefaultTabIndex(int index)
{
	if ((m_defaultIndex = index) < 0)
	{
		throw "Default Tab Index is less than zero!";
	}
}

void
IWin32_TabControl::invalidatePlacementParams()
{
	GetWindowRect(getHandle(), &rc);
	ScreenToClient(GetParent(m_hWnd), &offset);
	OffsetRect(&rc, offset.x, offset.y); //convert to client coordinates
	rc.top += 20;
}

void
IWin32_TabControl::addTabPage(const char* title, ITabPage* page)
{
	m_tci.pszText = (LPSTR)title;

	int curr = m_tabPages.size();

	TabCtrl_InsertItem(getHandle(), curr, &m_tci);

	SetWindowPos(page->getHandle(), 0, rc.left, rc.top, rc.right - rc.left - 20, rc.bottom - rc.top - 20, SWP_HIDEWINDOW);

	if (curr == m_defaultIndex) {
		page->show();
	}

	m_tabPages.push_back(page);
	
}

inline
void
IWin32_TabControl::doHideAll()
{
	for (auto t : m_tabPages)
	{
		t->hide();
	}
}

void
IWin32_TabControl::onTabSelectionChanged()
{
	doHideAll();
	m_tabPages[TabCtrl_GetCurSel(m_hWnd)]->show();
}