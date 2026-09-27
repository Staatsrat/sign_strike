#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <TraceLoggingProvider.h>

TRACELOGGING_DEFINE_PROVIDER(
    g_hProvider,
    "test",
    (0x8f5c2e71, 0x4a63, 0x4c92, 0x91, 0x37, 0x5e, 0xa4, 0x8b, 0x21, 0xd6, 0xf0)
);

#define ID_OK 1
#define ID_ERROR 2

static void LogEvent(const char* button)
{
    TraceLoggingWrite(
        g_hProvider,
        "ButtonPressed",
        TraceLoggingString(button, "Button")
    );
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_COMMAND:
            if (LOWORD(wParam) == ID_OK)
                LogEvent("OK");
            else if (LOWORD(wParam) == ID_ERROR)
                LogEvent("ERROR");
            break;

        case WM_DESTROY:
            TraceLoggingUnregister(g_hProvider);
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProcA(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    (void)hPrevInstance;
    (void)lpCmdLine;

    TraceLoggingRegister(g_hProvider);

    const char className[] = "TestWindow";

    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    wc.hCursor = LoadCursorA(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassA(&wc);

    HWND hwnd = CreateWindowExA(
        0,
        className,
        "test",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        330,
        180,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hwnd)
    {
        TraceLoggingUnregister(g_hProvider);
        return 1;
    }

    CreateWindowA(
        "STATIC",
        "test",
        WS_VISIBLE | WS_CHILD | SS_CENTER,
        15,
        15,
        285,
        20,
        hwnd,
        NULL,
        hInstance,
        NULL
    );

    CreateWindowA(
        "STATIC",
        "8f5c2e71-4a63-4c92-9137-5ea48b21d6f0",
        WS_VISIBLE | WS_CHILD | SS_CENTER,
        15,
        40,
        285,
        20,
        hwnd,
        NULL,
        hInstance,
        NULL
    );

    CreateWindowA(
        "BUTTON",
        "OK",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        35,
        80,
        110,
        35,
        hwnd,
        (HMENU)ID_OK,
        hInstance,
        NULL
    );

    CreateWindowA(
        "BUTTON",
        "ERROR",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        170,
        80,
        110,
        35,
        hwnd,
        (HMENU)ID_ERROR,
        hInstance,
        NULL
    );

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg;

    while (GetMessageA(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return 0;
}
