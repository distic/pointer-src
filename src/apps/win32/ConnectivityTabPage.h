#pragma once

#include "arch/arch_gui/IWin32_TabPage.h"
#include "arch/arch_gui/IWin32_CheckBox.h"
#include "arch/arch_gui/IWin32_GroupBox.h"
#include "arch/arch_gui/IWin32_ComboBox.h"

class ConnectivityTabPage : public ITabPage {
public:
	ConnectivityTabPage(HWND parent);
	virtual ~ConnectivityTabPage();

protected:
	void refreshNics();
	
	// Inherits via IWin32_TabPage
	void onCreateTabPage() override;

private:
	std::unique_ptr<ICheckBox> m_enableBluetooth;
	std::unique_ptr<IGroupBox> m_connectivityGroupBox;
	std::unique_ptr<IComboBox> m_selectedNic;
};