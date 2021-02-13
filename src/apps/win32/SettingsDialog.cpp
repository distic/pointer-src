#include "SettingsDialog.h"
#include "misc/resource.h"
#include "ConnectivityTabPage.h"

SettingsDialog::SettingsDialog() : IWindow(IDD_MAIN)
{
    // do nothing.
}

SettingsDialog::~SettingsDialog()
{
    // do nothing.
}

void SettingsDialog::onCreateWindow()
{
	setTitle("PowerTip Settings");
	// setTitleBarIcon(IDI_SMALL);

	m_okButton = std::make_unique<IButton>(m_hWnd, IDOK);
	m_cancelButton = std::make_unique<IButton>(m_hWnd, IDCANCEL);
	m_helpButton = std::make_unique<IButton>(m_hWnd, IDC_BUTTON_HELP);
	m_applyButton = std::make_unique<IButton>(m_hWnd, IDC_BUTTON_APPLY);

	m_tabCtrl = std::make_unique<ITabControl>(*this, IDC_TAB1);

	// m_generalTabPage = std::make_unique<GeneralTabPage>(m_tabCtrl->getHandle());
	m_optionsTabPage = std::make_unique<ConnectivityTabPage>(m_tabCtrl->getHandle());

	// m_tabCtrl->addTabPage("General", m_generalTabPage.get());
	m_tabCtrl->addTabPage("Connectivity", m_optionsTabPage.get());
}

void SettingsDialog::onFatalErrorRaised()
{
	close();
}