#include "AboutDialog.h"
#include "misc/resource.h"

AboutDialog::AboutDialog() : IWindow(IDD_ABOUTBOX)
{
	// do nothing.
}

AboutDialog::~AboutDialog()
{
	// do nothing.
}

void AboutDialog::onCreateWindow()
{
}

void AboutDialog::onFatalErrorRaised()
{
	close();
}