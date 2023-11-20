#include <windows.h>
#include "SnakeGame.h"
#include "Input.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register the window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"SnakeGameWindowClass";
    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,
        L"SnakeGameWindowClass",
        L"Snake Game",
        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU),
        CW_USEDEFAULT, CW_USEDEFAULT, 410, 440,
        nullptr, nullptr, hInstance, nullptr);

    if (hwnd == nullptr) {
        return 0;
    }

    // Show the window
    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        SnakeGame::Instance().Initialize(hwnd);
        break;
    case WM_TIMER:
        SnakeGame::Instance().Update();
        if (!SnakeGame::Instance().IsGameRunning()) {
            KillTimer(hwnd, 1);
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        SnakeGame::Instance().Render(hdc);
        EndPaint(hwnd, &ps);
    }
    break;
    case WM_KEYDOWN:
        Input::ProcessInput(hwnd, wParam, lParam);
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    case WM_DESTROY:
        SnakeGame::Instance().Cleanup();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
