#include "WindowManager.h"
#include <iostream>

// Static member variable definitions
int WindowManager::buffer_width;
int WindowManager::buffer_height;
unsigned int* WindowManager::pixels = nullptr;
void* WindowManager::buffer_memory = nullptr;
BITMAPINFO WindowManager::bmi;

HWND WindowManager::hwnd;
MSG WindowManager::msg;
HDC WindowManager::hdc;
bool WindowManager::running;

LRESULT CALLBACK WindowManager::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        running = false;
        PostQuitMessage(0);
        return 0;
    case WM_SIZE:
        RECT rect;
        GetClientRect(hwnd, &rect);

        buffer_width = rect.right - rect.left;
        buffer_height = rect.bottom - rect.top;

        pixels = (unsigned int*)buffer_memory;

        int buffer_size = buffer_width * buffer_height * sizeof(unsigned int);

        if (buffer_memory) VirtualFree(buffer_memory, 0, MEM_RELEASE);
        buffer_memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        pixels = new unsigned int[buffer_width * buffer_height];

        bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
        bmi.bmiHeader.biWidth = buffer_width;
        bmi.bmiHeader.biHeight = -buffer_height;  // Negative height to ensure top-down DIB
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;

        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

void WindowManager::Initialize(const wchar_t* name, const wchar_t* title, int width, int height) {
    class_name = name;
    window_title = title;
    window_width = width;
    window_height = height;
    running = true;
}

void WindowManager::Register(HINSTANCE hInstance) {
    WNDCLASS wc = {};

    wc.hInstance = hInstance;
    wc.lpszClassName = class_name;
    wc.lpfnWndProc = WindowProc;

    RegisterClass(&wc);
}

void WindowManager::CreateWindowInstance(HINSTANCE hInstance) {
    hwnd = CreateWindow(class_name, window_title, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, window_width, window_height,
        NULL, NULL, hInstance, NULL);
}

bool WindowManager::PeekMessages() {
    msg = {};
    return PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE) ? true : false;
}

void WindowManager::TranslateDispatch() {
    if (PeekMessages()) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void WindowManager::GetWindowContext() {
    hdc = GetDC(hwnd);
}

void WindowManager::ReleaseWindowContext() {
    ReleaseDC(hwnd, hdc);
}

void WindowManager::Rendering() {
    StretchDIBits(hdc, 0, 0, buffer_width, buffer_height, 0, 0, buffer_width, buffer_height, pixels, &bmi, DIB_RGB_COLORS, SRCCOPY);
}

void WindowManager::SetPixels(int x, int y) {
    if (pixels) {
        pixels[x + y * buffer_width] = 0xff500;
    }
}

void WindowManager::DrawLine(Vector2 A, Vector2 B) {
    int width = A.x - B.x;
    int height = A.y - B.y;
    double slope = height / width;
    double y_intercept = A.y - slope * A.x;
    
    //for (int x = (abs(width) >= abs(height)) ? min(A.x, B.x) : min(A.y, B.y);
    //	x <= (abs(width) >= abs(height)) ? max(A.x, B.x) : max(A.y, B.y); x++) {
    //	int y = round(x * slope + y_intercept);
    //	WindowManager::SetPixels(x, y);
    //}

    WindowManager wm;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            wm.SetPixels(i, j);
        }
    }
}

WindowManager::~WindowManager() {
    delete[] pixels;
}
