// PA4 Draft CAP4710.cpp : Defines the entry point for the application.
//
#pragma warning(disable : 4996)
#include "framework.h"
#include "PA5 Draft CAP4710.h"
#include "openGLPart.h"
#include <stdio.h>
#include <string>


#define MAX_LOADSTRING 100
HBITMAP g_hbmBall = NULL;
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

double BUNNY_SIZE = 0.1;
int NUMBER_OF_BUNNIES = 10;
BunnyColor bunnyColor = { 1.0, 0.0, 0.0 };
double SPEED = 0.008;
ColorPattern color = SOLID;
double THICKNESS = 0.03;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    NumberOfBunnies(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PA4DRAFTCAP4710, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PA4DRAFTCAP4710));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PA4DRAFTCAP4710));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PA4DRAFTCAP4710);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 830, 870, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
BOOL parseNumber(TCHAR str[]) {
    char str2[100];
    wcstombs(str2, str, wcslen(str));
    std::string str3 = str2;
    NUMBER_OF_BUNNIES = std::stoi(str3);
    return TRUE;
}

INT_PTR CALLBACK NumberOfBunnies(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{
    {
        TCHAR buffer[MAX_PATH];
        switch (message)
        {
        case WM_COMMAND:
            int x = LOWORD(wParam);
            switch (x)
            {
            case IDOK:
                GetDlgItemText(hDlg, IDC_EDIT1, buffer, sizeof(buffer));
                if (!parseNumber(buffer))
                    break;
                // Fall through. 
            case IDCANCEL:
                EndDialog(hDlg, wParam);
                return TRUE;
            }
        }
    }
    return (INT_PTR)FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        g_hbmBall = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_FILE_NEWGAME:
                openGLMain();
                break;
            case ID_APPLESIZE_SMALL:
                BUNNY_SIZE = 0.05;
                break;
            case ID_APPLESIZE_MEDIUM:
                BUNNY_SIZE = 0.1;
                break;
            case ID_APPLESIZE_LARGE:
                BUNNY_SIZE = 0.2;
                break;
            case ID_BUNNYCOLOR_RED:
                bunnyColor = { 1.0, 0.0, 0.0 };
                break;
            case ID_BUNNYCOLOR_BROWN:
                bunnyColor = { 0.588, 0.294, 0.0 };
                break;
            case ID_BUNNYCOLOR_GOLD:
                bunnyColor = { 1.0, 0.843, 0.0 };
                break;
            case ID_BUNNYCOLOR_WHITE:
                bunnyColor = { 1.0, 1.0, 1.0 };
                break;
            case ID_NUMBEROFAPPLES_5:
                NUMBER_OF_BUNNIES = 5;
                break;
            case ID_NUMBEROFAPPLES_10:
                NUMBER_OF_BUNNIES = 10;
                break;
            case ID_NUMBEROFAPPLES_20:
                NUMBER_OF_BUNNIES = 15;
                break;
            case ID_NUMBEROFAPPLES_CUSTOM:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, NumberOfBunnies);
                break;
            case ID_SNAKESPEED_SLOW:
                SPEED = 0.005;
                break;
            case ID_SNAKESPEED_MEDIUM:
                SPEED = 0.008;
                break;
            case ID_SNAKESPEED_FAST:
                SPEED = 0.012;
                break;
            case ID_SNAKECOLOR_SOLID:
                color = SOLID;
                break;
            case ID_SNAKECOLOR_CHECKERED:
                color = CHECKERED;
                break;
            case ID_SNAKECOLOR_HORIZONTALSTRIPPED:
                color = H_STRIPPED;
                break;
            case ID_SNAKECOLOR_VERTICALSTRIPPED:
                color - V_STRIPPED;
                break;
            case ID_SNAKESIZE_SMALL:
                THICKNESS = 0.01;
                break;
            case ID_SNAKESIZE_MEDIUM:
                THICKNESS = 0.03;
                break;
            case ID_SNAKESIZE_LARGE:
                THICKNESS = 0.05;
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            BITMAP bm;
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            HDC hdcMem = CreateCompatibleDC(hdc);
            HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, g_hbmBall);

            GetObject(g_hbmBall, sizeof(bm), &bm);

            BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

            SelectObject(hdcMem, hbmOld);
            DeleteDC(hdcMem);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
