#include "IWin32_ExceptionDialogBox.h"
#include <stdio.h>
#include <Uxtheme.h>

#include "../gui/win32/misc/resource.h" // HACK: shouldn't supposed to be here!!

#pragma comment(lib, "uxtheme.lib")

static EXCEPTION_RECORD CurrExceptionRecord;
static CONTEXT CurrContext;
static int iLastExceptionDlgResult;

static std::function<void()> m_f;

#define SetWindowThemeDlgItem(hwnd, id) SetWindowTheme(GetDlgItem(hwnd, id), L"", L"")

INT_PTR
IWin32_ExceptionDialogBox::DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	WORD wNotifyCode, wID;

	//
	// Article from MSDN:
	// https://docs.microsoft.com/en-us/windows/win32/directwrite/how-to-ensure-that-your-application-displays-properly-on-high-dpi-displays#gdi
	//

	// TODO: We need a way to detect DPI change during runtime and have these values update.
	HDC screen = GetDC(0);
	FLOAT dpiX = static_cast<FLOAT>(GetDeviceCaps(screen, LOGPIXELSX));
	FLOAT dpiY = static_cast<FLOAT>(GetDeviceCaps(screen, LOGPIXELSY));
	ReleaseDC(0, screen);

	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		SetWindowTheme(hwndDlg, L"", L"");
		SetWindowThemeDlgItem(hwndDlg, IDCANCEL);
		SetWindowThemeDlgItem(hwndDlg, IDC_EXCEPTION_DETAILS);
		SetWindowThemeDlgItem(hwndDlg, IDC_STATIC2);

		SetWindowText(hwndDlg, "Application Error");
		SetDlgItemText(hwndDlg, IDC_STATIC1, getExceptionCodeString(CurrExceptionRecord.ExceptionCode));
		ChangeFont(hwndDlg, IDC_STATIC1, static_cast<INT>(dpiX * 30.f / 96.f), "Segoe UI Bold");
		ChangeFont(hwndDlg, IDC_STATIC2, static_cast<INT>(dpiX * 15.f / 96.f), "Segoe UI");
		ChangeFont(hwndDlg, IDCANCEL, static_cast<INT>(dpiX * 15.f / 96.f), "Segoe UI");

		HWND h1058 = GetDlgItem(hwndDlg, 1058);
		HWND h1059 = GetDlgItem(hwndDlg, 1059);
		HWND h1060 = GetDlgItem(hwndDlg, 1060);

		char label2_content[MAX_PATH] = "";
		char label1_t_content[MAX_PATH] = "";
		char label1_b_content[MAX_PATH] = "";

#if _M_IX86
		SetDlgItemText(hwndDlg, ID_EXCEPTION_LABEL2, "EAX =\nEBX =\nECX =\nEDX =\nESI =\nEDI =\nEBP =");

		sprintf(label2_content,
			"%8.8X\n%8.8X\n%8.8X\n%8.8X\n%8.8X\n%8.8X\n%8.8X\n%8.8X",
			CurrContext.Eax,
			CurrContext.Ebx,
			CurrContext.Ecx,
			CurrContext.Edx,
			CurrContext.Esi,
			CurrContext.Edi,
			CurrContext.Ebp);

		sprintf(label1_t_content,
			"%8.8X\n%8.8X\n%8.8X\n%8.8X",
			CurrContext.SegDs,
			CurrContext.SegEs,
			CurrContext.SegFs,
			CurrContext.SegGs);

		sprintf(label1_b_content,
			"%8.8X\n%8.8X\n%8.8X",
			CurrContext.Eip,
			CurrContext.Esp,
			CurrContext.Ebp);
#else
		SetDlgItemText(hwndDlg, ID_EXCEPTION_LABEL2, "RAX =\nRBX =\nRCX =\nRDX =\nRSI =\nRDI =\nRBP =");

		sprintf(label2_content,
				"%8.8X\n%8.8X\n%8.8X\n%8.8X\n%8.8X\n%8.8X\n%8.8X\n%8.8X",
				CurrContext.Rax,
				CurrContext.Rbx,
				CurrContext.Rcx,
				CurrContext.Rdx,
				CurrContext.Rsi,
				CurrContext.Rdi,
				CurrContext.Rbp);

		sprintf(label1_t_content,
				"%8.8X\n%8.8X\n%8.8X\n%8.8X",
				CurrContext.SegDs,
				CurrContext.SegEs,
				CurrContext.SegFs,
				CurrContext.SegGs);

		sprintf(label1_b_content,
				"%8.8X\n%8.8X\n%8.8X",
				CurrContext.Rip,
				CurrContext.Rsp,
				CurrContext.Rbp);
#endif
		SetWindowText(h1058, label2_content);
		SetWindowText(h1059, label1_t_content);
		SetWindowText(h1060, label1_b_content);
	}
	break;

	case WM_DPICHANGED:
	{
	}
	break;

	case WM_COMMAND:
		wNotifyCode = HIWORD(wParam); // notification code
		wID = LOWORD(wParam);		  // item, control, or accelerator identifier
		if (wNotifyCode == BN_CLICKED)
		{
			if (wID == IDOK || wID == IDCANCEL)
				EndDialog(hwndDlg, wID);

			if (wID == IDC_COPY_EXCEPTION)
			{
				//CopyEditToClipboard(GetDlgItem(hwndDlg, IDC_EXCEPTION_DETAILS));
			}
		}

		break;
	}

	return FALSE;
}

const char *IWin32_ExceptionDialogBox::getExceptionCodeString(DWORD nativeExceptionCode)
{
	switch (nativeExceptionCode)
	{
	case EXCEPTION_ACCESS_VIOLATION:
		return "Access Violation";

	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
		return "Array Bounds Exceeded";

	case EXCEPTION_BREAKPOINT:
		return "Exception Breakpoint";

	case EXCEPTION_DATATYPE_MISALIGNMENT:
		return "Datatype Misalignment";

	case EXCEPTION_FLT_DENORMAL_OPERAND:
		return "Float Denormal Operand";

	case EXCEPTION_FLT_DIVIDE_BY_ZERO:
		return "Float Divide By Zero";

	case EXCEPTION_FLT_INEXACT_RESULT:
		return "Float Inexact Result";

	case EXCEPTION_FLT_INVALID_OPERATION:
		return "Float Invalid Operation";

	case EXCEPTION_FLT_OVERFLOW:
		return "Float Overflow";

	case EXCEPTION_FLT_STACK_CHECK:
		return "Float Stack Check";

	case EXCEPTION_FLT_UNDERFLOW:
		return "Underflow";

	case EXCEPTION_ILLEGAL_INSTRUCTION:
		return "Illegal Instruction";

	case EXCEPTION_IN_PAGE_ERROR:
		return "In Page Error";

	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		return "Integer Divide By Zero";

	case EXCEPTION_INT_OVERFLOW:
		return "Integer Overflow";

	case EXCEPTION_INVALID_DISPOSITION:
		return "Invalid Disposition";

	case EXCEPTION_NONCONTINUABLE_EXCEPTION:
		return "Noncontinuable Exception";

	case EXCEPTION_PRIV_INSTRUCTION:
		return "Private Instruction";

	case EXCEPTION_SINGLE_STEP:
		return "Single Step";

	case EXCEPTION_STACK_OVERFLOW:
		return "Stack Overflow";
	}

	return "Fatal Application Error";
}

int IWin32_ExceptionDialogBox::showDialog(EXCEPTION_POINTERS *ep)
{
	m_f();

	memcpy(&CurrExceptionRecord, ep->ExceptionRecord, sizeof(EXCEPTION_RECORD));
	memcpy(&CurrContext, ep->ContextRecord, sizeof(CONTEXT));

	//Show our exception dialog-box
	iLastExceptionDlgResult = DialogBoxParam(GetModuleHandle(0), MAKEINTRESOURCE(IDD_EXCEPTION), 0, IWin32_ExceptionDialogBox::DlgProc, 0);

	//return 1 in order to continue to run the program after the exception handling.
	return 1;
}

void IWin32_ExceptionDialogBox::finishCatch()
{
	if (iLastExceptionDlgResult == IDCANCEL)
	{
		//If the user selects "Terminate Application", exit from the program.
		ExitProcess(1);
	}
}

void IWin32_ExceptionDialogBox::addOnStopEvent(std::function<void()> f)
{
	m_f = f;
}