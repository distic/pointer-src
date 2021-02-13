#pragma once

#include "arch/arch_gui/IWin32_Window.h"

class AboutDialog : public IWindow {
public:
	AboutDialog();
	virtual ~AboutDialog();

protected:
	// Inherited via IWindow
	virtual void onCreateWindow() override;
	virtual void onFatalErrorRaised() override;
};