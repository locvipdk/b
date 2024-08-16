#include "WindowManager.h"

WindowManager wm;
Graphic2D g2d;

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	wm.Initialize(L"Hello", L"There", 1000, 720); 
	wm.Register(hInstance);
	wm.CreateWindowInstance(hInstance);
	wm.GetWindowContext();

	while (wm.running) {
		while (PeekMessage(&wm.msg, wm.hwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&wm.msg);
			DispatchMessage(&wm.msg);
		}
		Vector2 a = Vector2(0, 0);
		Vector2 b = Vector2(500, 500);
		g2d.DrawLine(a, b);

		wm.Rendering();
	}
	wm.ReleaseWindowContext();

	return 0;
}