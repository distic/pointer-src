#pragma once

#include "arch/arch_gui/IWin32_Window.h"
#include "arch/arch_gui/IWin32_Button.h"
#include "arch/arch_gui/IWin32_TabPage.h"
#include "arch/arch_gui/IWin32_TabControl.h"

#include <memory>

class SettingsDialog : public IWindow
{
public:
    SettingsDialog();
    virtual ~SettingsDialog();

    // Inherited via IWindow
    virtual void onCreateWindow() override;
    virtual void onFatalErrorRaised() override;

private:
	std::unique_ptr<ITabControl> m_tabCtrl;
	std::unique_ptr<ITabPage> m_optionsTabPage;

    std::unique_ptr<IButton> m_okButton;
    std::unique_ptr<IButton> m_cancelButton;
    std::unique_ptr<IButton> m_helpButton;
    std::unique_ptr<IButton> m_applyButton;
};