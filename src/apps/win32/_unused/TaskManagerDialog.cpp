#include "TaskManagerDialog.h"
#include "misc/resource.h"

TaskManagerDialog::TaskManagerDialog() : IDialogBox(IDD_TASKMGR)
{
    // do nothing.
}

TaskManagerDialog::~TaskManagerDialog()
{
    // do nothing.
}

void 
TaskManagerDialog::onCreateDialogBox()
{
    //m_listView = new IListView(m_hWnd, IDC_LIST1);

    //bindWmId(IDM_ENDTASK, [&]() { btnEndTask_Clicked(); });
    //bindWmId(IDM_SHUTDOWN, [&]() { btnShutdown_Clicked(); });
    //bindWmId(IDCANCEL, [&]() { btnCancel_Clicked(); });

    //auto v = TaskManager::getAllTasks();
    //for (std::vector<ITask*>::iterator it = v.begin(); it != v.end(); ++it) {
    //    IListViewItem lvItem;
    //    
    //    lvItem.setText((*it)->getName());
    //    lvItem.setIndex(0);
    //    lvItem.setSubItem(0);

    //    m_listView->addItem(lvItem);
    //}
}

void 
TaskManagerDialog::btnEndTask_Clicked()
{

}

void 
TaskManagerDialog::btnShutdown_Clicked()
{

}

void 
TaskManagerDialog::btnCancel_Clicked()
{
    
}