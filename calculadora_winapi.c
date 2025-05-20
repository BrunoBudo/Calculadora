#include <windows.h>
#include <stdio.h>

HWND hEdit1, hEdit2, hLabel;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        CreateWindow("STATIC", "Número 1:", WS_VISIBLE | WS_CHILD, 20, 20, 80, 20, hwnd, NULL, NULL, NULL);
        hEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 20, 100, 20, hwnd, NULL, NULL, NULL);

        CreateWindow("STATIC", "Número 2:", WS_VISIBLE | WS_CHILD, 20, 60, 80, 20, hwnd, NULL, NULL, NULL);
        hEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 60, 100, 20, hwnd, NULL, NULL, NULL);

        CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD, 20, 100, 50, 30, hwnd, (HMENU)1, NULL, NULL);
        CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD, 80, 100, 50, 30, hwnd, (HMENU)2, NULL, NULL);
        CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD, 140, 100, 50, 30, hwnd, (HMENU)3, NULL, NULL);
        CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD, 200, 100, 50, 30, hwnd, (HMENU)4, NULL, NULL);

        hLabel = CreateWindow("STATIC", "Resultado:", WS_VISIBLE | WS_CHILD, 20, 150, 200, 30, hwnd, NULL, NULL, NULL);
        break;
    }

    case WM_COMMAND: {
        char buf1[100], buf2[100];
        double n1, n2, res = 0;
        GetWindowText(hEdit1, buf1, 100);
        GetWindowText(hEdit2, buf2, 100);
        n1 = atof(buf1);
        n2 = atof(buf2);

        int op = LOWORD(wParam);
        switch (op) {
        case 1: res = n1 + n2; break;
        case 2: res = n1 - n2; break;
        case 3: res = n1 * n2; break;
        case 4:
            if (n2 == 0) {
                SetWindowText(hLabel, "Erro: divisão por zero!");
                return 0;
            }
            res = n1 / n2;
            break;
        }

        char result[100];
        sprintf(result, "Resultado: %.2f", res);
        SetWindowText(hLabel, result);
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "CalcWindowClass";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, "Calculadora C WinAPI", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, 300, 250,
                               NULL, NULL, hInst, NULL);

    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}