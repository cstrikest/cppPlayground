#ifndef UNICODE
#define UNICODE
#endif 

#include "stack.h"
#include "bmp.h"
#include "colors.h"
#include "image_func.h"
#include <Windows.h>
#include <tchar.h>

//https://pan.baidu.com/s/1rnJ-_hoeVcdAaOVghx2Lqg?pwd=njo0
//https://blog.csdn.net/memorywithyou/article/details/126607163
//https://blog.csdn.net/dengjin20104042056/article/details/115174639
//https://blog.csdn.net/vcjmd/article/details/125281085
//https://dengjin.blog.csdn.net/article/details/115068410
//https://dengjin.blog.csdn.net/article/details/122158699?spm=1001.2014.3001.5502&ydreferer=aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2RlbmdqaW4yMDEwNDA0MjA1Ni9hcnRpY2xlL2RldGFpbHMvMTE1MTc0NjM5

using namespace image_func;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

struct StateInfo
{
    LPCTSTR str;
    Stack stack;
};

StateInfo si{ _T("SB?"), Stack(100) };
StateInfo* pState;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t* name = L"Paineter";
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = name;

    //注册窗口类
    RegisterClass(&wc);

    //创建窗口
    HWND hwnd = CreateWindowEx(
        0L,                              // Optional window styles.
        name,                     // Window class
        L"Paineter",    // Window text
        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME ),            // Window style
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        &si      // Additional application data
    );

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

inline StateInfo* GetAppState(HWND hwnd)
{
    LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    StateInfo* pState = reinterpret_cast<StateInfo*>(ptr);
    return pState;
}

HWND getBtn(HWND hwnd)
{
    return CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"OK",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        10,         // x position 
        10,         // y position 
        100,        // Button width
        100,        // Button height
        hwnd,     // Parent window
        NULL,       // No menu.
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_CREATE)
    {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pState = reinterpret_cast<StateInfo*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pState);
    }
    else
    {
        pState = GetAppState(hwnd);
    }

    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
        EndPaint(hwnd, &ps);
    }
    return 0;

    case WM_CLOSE:
        if (MessageBox(hwnd, _T("Ready to quit?"), _T("Quit"), MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(hwnd);
        }
        return 0;

    case WM_LBUTTONDOWN:
        getBtn(hwnd);
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
