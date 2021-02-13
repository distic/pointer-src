#define WIN32_LEAN_AND_MEAN

#include "MainWindow.h"
#include "PowerTipApp.h"
#include "misc/resource.h"
#include "os/UserManager.h"
#include "nayuki/QR-Code-generator/cpp/QrCode.hpp"
#include "net/NetworkPal.h"

std::unique_ptr<qrcodegen::QrCode> m_qrCode;

MainWindow::MainWindow() : IWindow(IDD_DIALOG2),
						   m_isInit(true),
						   m_notifyIcon(nullptr)
{
	// do nothing.
}

MainWindow::~MainWindow()
{
	// do nothing.
}

void MainWindow::onCreateWindow()
{
	setTitleBarIcon(IDI_SMALL);

	if (m_notifyIcon == nullptr)
	{
		m_notifyIcon = std::make_unique<INotifyIcon>(getHandle(), IDI_SMALL);
		m_notifyIcon->setContextMenu(IDC_PROJECT1, 0);
		setNotifyIcon(m_notifyIcon.get());
	}

	m_notifyIcon->show();

	if (m_isInit)
	{
		m_isInit = false;

		bindWmId(ID_FILE_SETTINGS, [&]() { menuItem_File_Settings(); });
		bindWmId(ID_FILE_EXIT, [&]() { menuItem_File_Exit(); });

		// SetWindowLong(getHandle(), GWL_STYLE, WS_POPUP | WS_MINIMIZEBOX);
		SetWindowLong(getHandle(), GWL_EXSTYLE, 0);

		m_titleLabel = std::make_unique<ILabel>(m_hWnd, IDC_STATIC1);

		m_titleLabel->setFont(static_cast<INT>(dpiX * 17.f / 96.f), "Segoe UI");

		setTitle("PowerTip");

		refresh();
	}
}

void MainWindow::refresh()
{
	const qrcodegen::QrCode::Ecc errCorLvl = qrcodegen::QrCode::Ecc::LOW; // Error correction level

	std::string q = "";

	auto addrs = NetworkPal::getAddresses();

	for (int i = 0; i < addrs.size(); i++)
	{
		if (i == addrs.size() - 1)
			q += addrs[i];
		else
			q += addrs[i] + ";";
	}

	// Make and print the QR Code symbol
	m_qrCode = std::make_unique<qrcodegen::QrCode>(qrcodegen::QrCode::encodeText(q.c_str(), errCorLvl));
}

void MainWindow::onFatalErrorRaised()
{
	if (m_notifyIcon != nullptr)
	{
		m_notifyIcon->hide();
	}

	hide();
}

void MainWindow::menuItem_File_Exit()
{
	close();
}

void MainWindow::menuItem_File_Settings()
{
	m_settingsDialog = std::make_unique<SettingsDialog>();
	m_settingsDialog.get()->showDialog(getHandle());
}

void MainWindow::onPaint()
{
	PAINTSTRUCT ps;
	RECT rc;
	HDC hdcQrCode;
	HDC hdc = BeginPaint(m_hWnd, &ps);
	GetClientRect(m_hWnd, &rc);
	SetDCBrushColor(hdc, GetSysColor(COLOR_WINDOW));
	FillRect(hdc, &rc, (HBRUSH)GetStockObject(DC_BRUSH));

	HWND qrHwnd = GetDlgItem(getHandle(), IDC_QRCODE);

	hdcQrCode = BeginPaint(qrHwnd, &ps);

	COLORREF COLOR_WHITE = RGB(255, 255, 255);
	COLORREF COLOR_BLACK = RGB(0, 0, 0);

	int border = 0;

	for (int y = -border; y < m_qrCode->getSize() + border; y++)
	{
		for (int x = -border; x < m_qrCode->getSize() + border; x++)
		{
			SetPixel(hdcQrCode, x, y, m_qrCode->getModule(x, y) ? COLOR_BLACK : COLOR_WHITE);
		}
	}

	const int qrWidth = 96;
	const int qrHeight = 96;

	int qrWidthN = static_cast<INT>(dpiX * qrWidth / 96.f);
	int qrHeightN = static_cast<INT>(dpiY * qrHeight / 96.f);

	::StretchBlt(hdcQrCode, 0, 0, qrWidthN, qrHeightN, hdcQrCode, 0, 0, m_qrCode->getSize(), m_qrCode->getSize(), SRCCOPY);

	MoveWindow(qrHwnd, (rc.right - qrWidthN) / 2, ((rc.bottom - qrHeightN) / 2) + m_titleLabel->getHeight() / 2, qrWidthN, qrHeightN, TRUE);

	EndPaint(qrHwnd, &ps);
	EndPaint(m_hWnd, &ps);
}

int MainWindow::onCtlColorStatic(WPARAM wParam)
{
	static HBRUSH hBrushColor;
	if (!hBrushColor)
	{
		hBrushColor = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
		SetBkColor((HDC)wParam, GetSysColor(COLOR_WINDOW));
	}

	return reinterpret_cast<LRESULT>(hBrushColor);
}

void MainWindow::onNotifyIconPrimaryClick()
{
	if (isVisibe())
		hide();
	else
		show();
}

void MainWindow::onNotifyIconSecondaryClick()
{
	m_notifyIcon->showContextMenu();
}

void MainWindow::onWindowLostFocus()
{
	// hide();
}