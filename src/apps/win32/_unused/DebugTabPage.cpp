#include "DebugTabPage.h"
#include "TaskManagerDialog.h"
#include "misc/resource.h"

DebugTabPage::DebugTabPage(HWND tab) : ITabPage(tab, IDD_TAB_CHILD3)
{
	// do nothing.
}

DebugTabPage::~DebugTabPage()
{
	if (m_taskManagerButton != nullptr) {
		delete m_taskManagerButton;
		m_taskManagerButton = nullptr;
	}
}

void 
DebugTabPage::onCreateTabPage()
{
	m_taskManagerButton = new IButton(m_hWnd, IDM_TASKMGR);

	bindWmId(IDM_TASKMGR, [&]() { taskManagerButton_Clicked(); });
}

void 
DebugTabPage::taskManagerButton_Clicked()
{
	TaskManagerDialog dialog;
	dialog.showDialog(m_hWnd);
}