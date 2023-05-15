#ifndef UNICODE
#define UNICODE
#endif 

#include "stack.h"
#include "bmp.h"
#include "colors.h"
#include "image_func.h"
#include <Windows.h>
#include <tchar.h>

using namespace image_func;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t* name = L"Paineter";
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = name;

    //注册窗口类
    RegisterClass(&wc);

    //创建菜单
    HMENU hMenu = CreateMenu();
    InsertMenu(hMenu, 0, 1, 0, NULL);

    //创建窗口
    HWND hwnd = CreateWindowEx(
        0L,                              // Optional window styles.
        name,                     // Window class
        L"Paineter",    // Window text
        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME ),            // Window style
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,       // Parent window    
        hMenu,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


//int main()
//{
//	//runStack();
//	try
//	{
//		Bmp t("b.bmp");
//		t.getImageBgr24b() >> fullReverse;
//		t.save("s.bmp");
//	}
//	catch (std::exception& e)
//	{
//		std::cout << e.what() << std::endl;
//	}
//	return 0;
//}
