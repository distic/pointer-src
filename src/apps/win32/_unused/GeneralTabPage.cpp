#include "GeneralTabPage.h"
#include "misc/resource.h"

#include "PowerTipApp.h"

GeneralTabPage::GeneralTabPage(HWND tab) : ITabPage(tab, IDD_TAB_CHILD1)
// m_powtipsProxy(App->getPowtipsProxy()),
// m_powtipd(App->getPowtipd())
{
	// do nothing.
}

GeneralTabPage::~GeneralTabPage()
{
	if (m_serviceStatusLabel != nullptr) {
		delete m_serviceStatusLabel;
		m_serviceStatusLabel = nullptr;
	}

	if (m_serviceLastRunLabel != nullptr) {
		delete m_serviceLastRunLabel;
		m_serviceLastRunLabel = nullptr;
	}

	if (m_serviceToggleButton != nullptr) {
		delete m_serviceToggleButton;
		m_serviceToggleButton = nullptr;
	}
}

void
GeneralTabPage::onCreateTabPage()
{
	bindWmId(IDC_BUTTON1, [&]() { serviceToggleButton_Clicked(); });

	m_serviceStatusLabel = new ILabel(m_hWnd, IDC_STATIC1);
	m_serviceLastRunLabel = new ILabel(m_hWnd, IDC_STATIC2);
	m_serviceToggleButton = new IButton(m_hWnd, IDC_BUTTON1);

	m_serviceStatusLabel->setFont(14, "Segoe UI Bold");
	m_serviceLastRunLabel->setFont(14, "Segoe UI");
}

void
GeneralTabPage::serviceToggleButton_Clicked()
{
	if (isPowtipsRunning()) {
		doStopService();
	} else {
		doStartService();
	}
}

void
GeneralTabPage::doStartService()
{
	if (isPowtipsRunning()) {
		// MessageBox(getHandle(), "Another instance of the POWTIPS is already running in the background!", "PowerTip", MB_ICONEXCLAMATION);
	} else {
		// m_powtipsProxy.startProcess();
	}
}

void
GeneralTabPage::doStopService()
{
	if (isPowtipsRunning()) {
		// m_powtipsProxy.killProcess();
	} else {
		// MessageBox(getHandle(), "Already killed POWTIPS previously!", "PowerTip", MB_ICONEXCLAMATION);
	}
}

inline
bool 
GeneralTabPage::isPowtipsRunning() const
{
	return false;// m_powtipsProxy.isRunning();
}