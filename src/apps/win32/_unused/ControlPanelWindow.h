#pragma once

#include "TaskManagerDialog.h"
#include "arch/arch_gui/IWin32_Window.h"
#include "arch/arch_gui/IWin32_TabControl.h"
#include "arch/arch_gui/IWin32_Button.h"

#include "GeneralTabPage.h"
#include "ConnectivityTabPage.h"

class MainWindow : public IWindow {
public:
	MainWindow();
	virtual ~MainWindow();

protected:
	// Inherits via IWin32_Window
	void onCreateWindow() override;

public:
	void btnOk_Clicked();
	void btnCancel_Clicked();
	void btnHelp_Clicked();
	void btnApply_Clicked();

	GeneralTabPage* getGeneralTabPage() const;

private:
	std::unique_ptr<ITabControl> m_tabCtrl;
	std::unique_ptr<ITabPage> m_generalTabPage;
	std::unique_ptr<ITabPage> m_optionsTabPage;
#if _DEBUG
	std::unique_ptr<ITabPage> m_debugTabPage;
#endif
	std::unique_ptr<IButton> m_okButton;
	std::unique_ptr<IButton> m_cancelButton;
	std::unique_ptr<IButton> m_helpButton;
	std::unique_ptr<IButton> m_applyButton;
};