#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "framework.h"
#include <windows.h>  
#include <vector> 
#include "lab2.2.h"
struct Leaks {
    ~Leaks() { _CrtDumpMemoryLeaks(); }
}_l;
 

// Объекты окна  
HWND g_hWnd;
HDC g_hdc;
PAINTSTRUCT g_ps;

// Классы фигур  
class Shape {
public:
    virtual void Draw(HDC hdc) = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    int m_x, m_y, m_r;
public:
    Circle(int x, int y, int r) : m_x(x), m_y(y), m_r(r) {}
    virtual void Draw(HDC hdc) {
        Ellipse(hdc, m_x - m_r, m_y - m_r, m_x + m_r, m_y + m_r);
    }
};

class Rect : public Shape {
private:
    int m_x, m_y, m_w, m_h;
public:
    Rect(int x, int y, int w, int h) : m_x(x), m_y(y), m_w(w), m_h(h) {}
    virtual void Draw(HDC hdc) {
        Rectangle(hdc, m_x, m_y, m_x + m_w, m_y + m_h);
    }
};

// Контейнер для фигур  
std::vector<Shape*> g_shapes;

// Обработчик сообщений  
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE: {
        // Создание фигур  
        Circle* circle = new Circle(50, 50, 30);
        Rect* rect = new Rect(100, 100, 50, 30);

        // Добавление в контейнер  
        g_shapes.push_back(circle);
        g_shapes.push_back(rect);
        break;
    }
    case WM_PAINT: {
        g_hdc = BeginPaint(hWnd, &g_ps);

        // Рисование фигур из контейнера  
        for (int i = 0; i < g_shapes.size(); i++) {
            g_shapes[i]->Draw(g_hdc);
        }

        EndPaint(hWnd, &g_ps);
        break;
    }
    case WM_DESTROY: {
        for (int i = 0; i < g_shapes.size(); i++) {
            delete g_shapes[i];
        }
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Регистрация класса окна  
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"MyWindowClass";
    RegisterClass(&wc);

    // Создание окна  
    g_hWnd = CreateWindow(L"MyWindowClass", L"Windows Application", WS_OVERLAPPEDWINDOW,
        0, 0, 640, 480, NULL, NULL, hInstance, NULL);

    ShowWindow(g_hWnd, nCmdShow);

    // Обработка сообщений  
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
