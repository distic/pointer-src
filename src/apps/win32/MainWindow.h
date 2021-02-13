#pragma once

#include "arch/arch_gui/IWin32_Window.h"
#include "arch/arch_gui/IWin32_Label.h"
#include "core/PowtipdProxy.h"
#include "core/IPowtipsEventListener.h"
#include "SettingsDialog.h"

class MainWindow : public IWindow
{
public:
    MainWindow();
    virtual ~MainWindow();

    void startPowtips();
    void stopPowtips();

    INotifyIcon& getNotifyIcon() const {
        return *m_notifyIcon;
    }

private:
    virtual void menuItem_File_Exit();
    virtual void menuItem_File_Settings();

    void refresh();

    virtual void onFatalErrorRaised() override;

protected:
    // Inherited via IWindow
    virtual void onCreateWindow() override;
    virtual void onPaint() override;
    virtual int onCtlColorStatic(WPARAM wParam) override; // HACK: shouldn't event exist!!!!!
    virtual void onNotifyIconPrimaryClick() override;
    virtual void onNotifyIconSecondaryClick() override;
    virtual void onWindowLostFocus() override;

private:
    bool m_isInit;
    std::unique_ptr<ILabel> m_titleLabel;
    std::unique_ptr<SettingsDialog> m_settingsDialog;
    std::unique_ptr<INotifyIcon> m_notifyIcon;
};