#include "framework.h" 
#include "WindowsProject1.h" 
#include <Windows.h> 

class Vector2D {
    friend void DrawEllipse(HDC, const Vector2D&, double);
    friend Vector2D operator+(const Vector2D& left, const Vector2D& right);
private:
    float x, y;
public:
    Vector2D(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
    virtual ~Vector2D() {}
};

Vector2D operator+(const Vector2D& left, const Vector2D& right) {
    return Vector2D(left.x + right.x, left.y + right.y);
}

void DrawEllipse(HDC hdc, const Vector2D& center, double radius) {
    Ellipse(hdc, static_cast<int>(center.x - radius), static_cast<int>(center.y - radius), static_cast<int>(center.x + radius), static_cast<int>(center.y + radius));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        const double radius = 40.0;
        const double margin = 70.0;
        const int num_circles = 9;

        Vector2D centers[num_circles];
        for (int i = 0; i < num_circles; i++) {
            centers[i] = Vector2D(margin + (i % 3) * (radius * 2 + margin), margin + (i / 3) * (radius * 2 + margin));
        }

        int i = 0;
        while (i < num_circles) {
            DrawEllipse(hdc, centers[i], radius);
            i++;
        }

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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"WindowClass";
    RegisterClass(&wc);

    HWND hWnd = CreateWindow(wc.lpszClassName, L"Ellipses", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, nullptr, nullptr, hInstance, nullptr);
    ShowWindow(hWnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}
