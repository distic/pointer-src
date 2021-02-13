#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>
#include <scrnsave.h>
#include <CommCtrl.h>

#pragma comment(lib, "scrnsave.lib")
#pragma comment(lib, "comctl32.lib")

//globals used by the function below to hold the screen size
int Width;
int Height;

//define a Windows timer
#define TIMER 1

BOOL WINAPI RegisterDialogClasses(
    HANDLE hInst)
{
    return TRUE;
}

BOOL WINAPI ScreenSaverConfigureDialog(
    HWND hDlg,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
    return FALSE;
}

// Screen Saver Procedure
LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT message,
                               WPARAM wParam, LPARAM lParam)
{
    static HDC hDC;
    static HGLRC hRC;
    static RECT rect;

    switch (message)
    {

    case WM_CREATE:
        // get window dimensions
        GetClientRect(hWnd, &rect);
        Width = rect.right;
        Height = rect.bottom;

        //get configuration from registry if applicable

        //set up OpenGL
        // InitGL( hWnd, hDC, hRC );

        //Initialize perspective, viewpoint, and
        //any objects you wish to animate

        //create a timer that ticks every 10 milliseconds
        SetTimer(hWnd, TIMER, 10, NULL);

        return 0;

    case WM_CTLCOLORSTATIC:
    {
        static HBRUSH hBrushColor;
        if (!hBrushColor)
        {
            hBrushColor = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
            SetBkColor((HDC)wParam, GetSysColor(COLOR_WINDOW));
        }
        return (LRESULT)hBrushColor;
    }

    case WM_DRAWITEM:
    {
        LPDRAWITEMSTRUCT Item;
        Item = (LPDRAWITEMSTRUCT)lParam;
        SelectObject(Item->hDC, CreateFont(16, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial Black"));
        FillRect(Item->hDC, &Item->rcItem, CreateSolidBrush(0));
        SelectObject(Item->hDC, CreateSolidBrush(0));
        if (Item->itemState & ODS_SELECTED)
        {
            SetTextColor(Item->hDC, 0);
            SelectObject(Item->hDC, CreateSolidBrush(0xFF00));
            SelectObject(Item->hDC, CreatePen(PS_SOLID, 2, 0xFF00));
        }
        else
        {
            SetTextColor(Item->hDC, 0x00FF00);
            SelectObject(Item->hDC, CreatePen(PS_SOLID, 2, 0x00FF00));
        }
        SetBkMode(Item->hDC, TRANSPARENT);
        RoundRect(Item->hDC, Item->rcItem.left, Item->rcItem.top, Item->rcItem.right, Item->rcItem.bottom, 20, 20);
        int len;
        len = GetWindowTextLength(Item->hwndItem);
        LPSTR lpBuff;
        lpBuff = new char[len + 1];
        GetWindowTextA(Item->hwndItem, lpBuff, len + 1);
        DrawTextA(Item->hDC, lpBuff, len, &Item->rcItem, DT_CENTER);
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        RECT rc;
        HDC hdc = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &rc);
        SetDCBrushColor(hdc, GetSysColor(COLOR_WINDOW));
        FillRect(hdc, &rc, (HBRUSH)GetStockObject(DC_BRUSH));

        //or use ps.rcPaint to repaint only the section which requires update
        //FillRect(hdc, &ps.rcPaint, (HBRUSH)GetStockObject(DC_BRUSH));

        EndPaint(hWnd, &ps);
        return 0;
    }

    case WM_DESTROY:
        KillTimer(hWnd, TIMER);

        //delete any objects created during animation
        //and close down OpenGL nicely

        //  CloseGL( hWnd, hDC, hRC );
        return 0;

    case WM_TIMER:
        //call some function to advance your animation
        return 0;
    }

    //let the screensaver library take care of any
    //other messages

    return DefScreenSaverProc(hWnd, message, wParam, lParam);
}