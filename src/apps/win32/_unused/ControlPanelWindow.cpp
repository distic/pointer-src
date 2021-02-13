#include "MainWindow.h"
#include "misc/resource.h"
#include "TaskManagerDialog.h"
#include "arch/arch_gui/IWin32_TabPage.h"
#include "GeneralTabPage.h"
#include "ConnectivityTabPage.h"
#include <assert.h>

#if _DEBUG
#include "DebugTabPage.h"
#endif

MainWindow::MainWindow() : IWindow(IDD_MAIN),
	m_generalTabPage(nullptr),
	m_applyButton(nullptr),
	m_cancelButton(nullptr),
#if _DEBUG
	m_debugTabPage(nullptr),
#endif
	m_helpButton(nullptr),
	m_tabCtrl(nullptr),
	m_optionsTabPage(nullptr)
{
	// do nothing.
}

MainWindow::~MainWindow()
{
	// do nothing.
}

void
MainWindow::onCreateWindow()
{
	setTitle("PowerTip");
	setTitleBarIcon(IDI_SMALL);

	//registerNotifyIcon();

	m_okButton = std::make_unique<IButton>(m_hWnd, IDOK);
	m_cancelButton = std::make_unique<IButton>(m_hWnd, IDCANCEL);
	m_helpButton = std::make_unique<IButton>(m_hWnd, IDC_BUTTON_HELP);
	m_applyButton = std::make_unique<IButton>(m_hWnd, IDC_BUTTON_APPLY);

	m_tabCtrl = std::make_unique<ITabControl>(*this, IDC_TAB1);

	// m_generalTabPage = std::make_unique<GeneralTabPage>(m_tabCtrl->getHandle());
	m_optionsTabPage = std::make_unique<ConnectivityTabPage>(m_tabCtrl->getHandle());

	// m_tabCtrl->addTabPage("General", m_generalTabPage.get());
	m_tabCtrl->addTabPage("Options", m_optionsTabPage.get());

#if _DEBUG
	// m_tabCtrl->addTabPage("Debug", m_debugTabPage = new DebugTabPage(m_tabCtrl->getHandle()));
#endif

	bindWmId(IDOK, [&]() { btnOk_Clicked(); });
	bindWmId(IDCANCEL, [&]() { btnCancel_Clicked(); });
	bindWmId(IDC_BUTTON_HELP, [&]() { btnHelp_Clicked(); });
	bindWmId(IDC_BUTTON_APPLY, [&]() { btnApply_Clicked(); });
}

void
MainWindow::btnOk_Clicked()
{
	close();
}

void
MainWindow::btnCancel_Clicked()
{
	close();
}

void
MainWindow::btnHelp_Clicked()
{
	MessageBox(m_hWnd, "Help content is currently unavailable!", "PowerTip", MB_ICONEXCLAMATION);
}

void
MainWindow::btnApply_Clicked()
{
	m_applyButton->setEnabled(false);
}

GeneralTabPage* 
MainWindow::getGeneralTabPage() const
{
	assert(m_generalTabPage != nullptr);
	return reinterpret_cast<GeneralTabPage*>(m_generalTabPage.get());
}