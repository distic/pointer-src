#pragma once

#include "app/GuiApp.h"
#include "MainWindow.h"
#include "arch/arch_gui/IWin32_WinMain.h"

class PowerTipApp : public GuiApp {
public:
	PowerTipApp();
	virtual ~PowerTipApp();

private:
    // Inherited via GuiApp
    virtual void showMessageBox(std::string title, std::string text) override;
    virtual void showToast(std::string title, std::string body) override;
    virtual int runPlatformLooper() override;
    virtual void close() override;
    virtual void onStopping() override;
    virtual void onStarting() override;
    virtual void onCleaning() override;

private:
	//
	// Win32-specific(s)
	//
	IWin32_WinMain* m_winMain;
};