#pragma once

#include "arch/arch_gui/IWin32_DialogBox.h"
#include "arch/arch_gui/IWin32_ListView.h"

class TaskManagerDialog : public IDialogBox {
public:
	TaskManagerDialog();
	virtual ~TaskManagerDialog();

	void btnEndTask_Clicked();
	void btnShutdown_Clicked();
	void btnCancel_Clicked();

protected:

	// Inherits via IWin32_DialogBox
	void onCreateDialogBox() override;

private:
	std::unique_ptr<IListView> m_listView;
};