#pragma once
#include "functions.h"

class WindowManager : public SetUpPixels , public Graphic2D {
private:
    const wchar_t* class_name;
    const wchar_t* window_title;
    int window_width, window_height;

public:
    static int buffer_width;
    static int buffer_height;
    static unsigned int* pixels;
    static void* buffer_memory;
    static BITMAPINFO bmi;

    static HWND hwnd;
    static MSG msg;
    static HDC hdc;
    static bool running;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    void Initialize(const wchar_t* name, const wchar_t* title, int width, int height);
    void Register(HINSTANCE hInstance);
    void CreateWindowInstance(HINSTANCE hInstance);
    bool PeekMessages();
    void TranslateDispatch();
    void GetWindowContext();
    void ReleaseWindowContext();
    void Rendering();
    void SetPixels(int x, int y) override;
    void DrawLine(Vector2 A, Vector2 B) override;

    ~WindowManager();
};



//BITMAPINFO WindowManager::bmi;
//int WindowManager::buffer_height;
//int WindowManager::buffer_width;
//unsigned int* WindowManager::pixels;
//void* WindowManager::buffer_memory;