#include <windows.h>
#include <string>
#include <sstream>

HWND hEdit1, hEdit2, hLabel;

double getNumber(HWND hWnd) {
    char buffer[100];
    GetWindowTextA(hWnd, buffer, 100);
    return atof(buffer);
}

void showResult(double result) {
    std::ostringstream oss;
    oss << "Resultado: " << result;
    SetWindowTextA(hLabel, oss.str().c_str());
}

void showError(const char* msg) {
    SetWindowTextA(hLabel, msg);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        CreateWindowA("STATIC", "Número 1:", WS_VISIBLE | WS_CHILD, 20, 20, 80, 20, hwnd, NULL, NULL, NULL);
        hEdit1 = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 20, 100, 20, hwnd, NULL, NULL, NULL);

        CreateWindowA("STATIC", "Número 2:", WS_VISIBLE | WS_CHILD, 20, 60, 80, 20, hwnd, NULL, NULL, NULL);
        hEdit2 = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 60, 100, 20, hwnd, NULL, NULL, NULL);

        CreateWindowA("BUTTON", "+", WS_VISIBLE | WS_CHILD, 20, 100, 50, 30, hwnd, (HMENU)1, NULL, NULL);
        CreateWindowA("BUTTON", "-", WS_VISIBLE | WS_CHILD, 80, 100, 50, 30, hwnd, (HMENU)2, NULL, NULL);
        CreateWindowA("BUTTON", "*", WS_VISIBLE | WS_CHILD, 140, 100, 50, 30, hwnd, (HMENU)3, NULL, NULL);
        CreateWindowA("BUTTON", "/", WS_VISIBLE | WS_CHILD, 200, 100, 50, 30, hwnd, (HMENU)4, NULL, NULL);

        hLabel = CreateWindowA("STATIC", "Resultado:", WS_VISIBLE | WS_CHILD, 20, 150, 200, 30, hwnd, NULL, NULL, NULL);
        break;
    }
    case WM_COMMAND: {
        double a = getNumber(hEdit1);
        double b = getNumber(hEdit2);
        double res = 0;

        switch (LOWORD(wParam)) {
        case 1: res = a + b; showResult(res); break;
        case 2: res = a - b; showResult(res); break;
        case 3: res = a * b; showResult(res); break;
        case 4:
            if (b == 0) showError("Erro: divisão por zero!");
            else { res = a / b; showResult(res); }
            break;
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {
    const char CLASS_NAME[] = "CalcWinClass";

    WNDCLASSA wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClassA(&wc);

    HWND hwnd = CreateWindowExA(
        0, CLASS_NAME, "Calculadora C++ WinAPI", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 250,
        NULL, NULL, hInst, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessageA(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return 0;
}