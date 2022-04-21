#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "shapes.h"

#define RED (RGB(255, 0, 0))
#define GREEN (RGB(0, 255, 0))
#define BLUE (RGB(0, 0, 255))
#define BLACK (RGB(0, 0, 0))
#define WHITE (RGB(255, 255, 255))

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

	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT {
		static std::ofstream os("debug.txt");

		static int width, height;
		static KShape* shape = nullptr;

		switch (uMsg) {
		case WM_SIZE:
			width = LOWORD(lParam);
			height = HIWORD(lParam);
			break;

		case WM_PAINT: 
			if (!shape) 
				shape = new KCircle(hWnd, width / 2, height / 2, 100);	
			shape->MoveTo(width / 2, height / 2);
			shape->Show();
			break;

		case WM_LBUTTONDOWN:
			shape->MoveTo(LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_KEYDOWN: {
			switch (wParam) {
			case VK_NUMPAD1: 
				delete shape;
				shape = new KCircle(hWnd, width / 2, height / 2, 100);
				shape->Show();
				break;
			case VK_NUMPAD2:
				delete shape;
				shape = new KCustomCircle(hWnd, width / 2, height / 2, 100);
				shape->Show();
				break;
			case VK_NUMPAD3:
				delete shape;
				shape = new KParallelogram(hWnd, 100, 100, 100, 150, 120);
				shape->MoveTo(width / 2, height / 2);
				shape->Show();
				break;
			case VK_NUMPAD4:
				delete shape;
				shape = new KParallelogramWithDiagonals(hWnd, 100, 100, 100, 150, 120);
				shape->MoveTo(width / 2, height / 2);
				shape->Show();
				break;
			case VK_NUMPAD5:
				delete shape;
				shape = new KColoredParallelogram(hWnd, 100, 100, 100, 150, 120);
				shape->MoveTo(width / 2, height / 2);
				shape->Show();
				break;
			case VK_NUMPAD6:
				delete shape;
				shape = new KColoredParallelogram(hWnd, 100, 100, 100, 150, 120, RED, GREEN, BLUE, BLACK);
				shape->MoveTo(width / 2, height / 2);
				shape->Show();
				break;
			case VK_RIGHT:
				shape->Shift(50, 0);
				break;
			case VK_LEFT:
				shape->Shift(-50, 0);
				break;
			case VK_UP:
				shape->Shift(0, -50);
				break;
			case VK_DOWN:
				shape->Shift(0, 50);
				break;
			case VK_ADD:
				shape->Expand(1.2);
				break;
			case VK_SUBTRACT:
				shape->Expand(1/1.2);
				break;
			case VK_DELETE:
				shape->Rotate(20);
				break;
			default:
				shape->ToggleVisible();
				break;
			}
		} break;

		case WM_DESTROY:
			PostQuitMessage(EXIT_SUCCESS);
			break;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	};

	if (!RegisterClassEx(&wc)) {
		MessageBox(nullptr, L"Ошибка создания класса", L"Ошибка", MB_OK | MB_ICONSTOP);
		return NULL;
	}

	HWND hwnd = CreateWindow(
		wc.lpszClassName, L"Geom shapes",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
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
