#include "PowerTipApp.h"
#include "arch/arch_gui/IWin32_ExceptionDialogBox.h"
#include <assert.h>

#if SYSAPI_UWP
#define CREATE_POWTIPD 1
#else
#define CREATE_POWTIPD 0
#endif

PowerTipApp::PowerTipApp() : GuiApp(CREATE_POWTIPD),
							 m_winMain(new IWin32_WinMain(*new MainWindow()))
{
    m_winMain->registerExtraLoopFunction([&] { onMainLoop(); });
}

PowerTipApp::~PowerTipApp()
{
	// do nothing.
}

void PowerTipApp::showMessageBox(std::string title, std::string text)
{
	MessageBoxA(HWND_DESKTOP, text.c_str(), title.c_str(), MB_ICONERROR);
}

void PowerTipApp::showToast(std::string title, std::string body)
{
	static_cast<MainWindow *>(m_winMain->getMainWindow())->getNotifyIcon().showToast(title, body);
}

int PowerTipApp::runPlatformLooper()
{
	assert(m_winMain != nullptr);
	m_winMain->runWindowsLooper();
	return 0;
}

void PowerTipApp::close()
{
	assert(m_winMain != nullptr);
	m_winMain->getMainWindow()->close();
}

void PowerTipApp::onStopping()
{
	for (auto w : IWindow::getAllWindows())
	{
		w->onFatalErrorRaised();
	}
}

void PowerTipApp::onStarting()
{
	IWin32_ExceptionDialogBox::addOnStopEvent([&] {
		onStop(1, std::string(""));
	});
}

void PowerTipApp::onCleaning()
{
	if (m_winMain != nullptr)
	{
		delete m_winMain;
		m_winMain = nullptr;
	}
}