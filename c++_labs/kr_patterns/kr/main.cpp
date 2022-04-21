#pragma comment(linker, "\"/manifestdependency:type='win32' \ name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \ processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "MVC.h"
#include "Resource.h"

#include <windows.h>
#include <iostream>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static SetModel* model;
	static View* view;
	static Controller* controller;

	switch (uMsg) {
	case WM_CREATE:
		model = new SetModel;
		controller = new Controller(model);
		view = new View(hWnd, model);
		break;
	case WM_PAINT: 
		view->Update();
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDB_ADD_BUTTON:
			controller->AddButtonClicked(view->GetEditValue());
			break;
		case IDB_CHANGE_VIEW:
			view->ChangeView();
			break;
		case IDB_SAVE_BUTTON:
			controller->Save();
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };

	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = L"WindowClass";

	wc.lpfnWndProc = WndProc;

	if (!RegisterClassEx(&wc)) {
		MessageBox(nullptr, L"Ошибка создания класса", L"Ошибка", MB_OK | MB_ICONSTOP);
		return NULL;
	}

	HWND hwnd = CreateWindow(
		wc.lpszClassName, L"MVC",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 890, 540,
		nullptr, nullptr, hInstance, nullptr
	);

	if (hwnd == INVALID_HANDLE_VALUE) {
		MessageBox(nullptr, L"Ошибка создания окна", L"Ошибка", MB_OK | MB_ICONSTOP);
		return NULL;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return msg.wParam;
}
