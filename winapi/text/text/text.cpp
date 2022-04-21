#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define CHANGE_COLOR 100

void AddMenu(HWND);

DWORD dColors[3] = { 0, 0, 0 };

std::vector<LPCWSTR> fonts{
	L"Times New Roman", 
	L"Consolas",
	L"Calibri",
	L"Courier New",
	L"Arial Black",
	L"Cambria",
	L"Bauhaus 93",
	L"Harlow Solid Italic"
};
LOGFONT lf;
void SetFont(int id) { wcscpy_s(lf.lfFaceName, fonts[id]); }
std::wstring str; 

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

	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfPitchAndFamily = DEFAULT_PITCH;
	wcscpy_s(lf.lfFaceName, L"Consolas");
	lf.lfHeight = 45;
	lf.lfWeight = 40;
	lf.lfWidth = 20;
	lf.lfEscapement = 0;

	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT {
		static int width, height;
		static COLORREF color = RGB(0, 0, 0);

		CHOOSECOLOR cc;
		cc.Flags = CC_RGBINIT;
		cc.hInstance = nullptr;
		cc.hwndOwner = hWnd;
		cc.lCustData = 0L;
		cc.lpCustColors = dColors;
		cc.lpfnHook = nullptr;
		cc.lpTemplateName = (LPCWSTR)nullptr;
		cc.lStructSize = sizeof(cc);
		cc.rgbResult = RGB(0, 0, 0);

		switch (uMsg) {
		case WM_CREATE:
			AddMenu(hWnd);
			break;
		case WM_SIZE:
			width = LOWORD(lParam);
			height = HIWORD(lParam);
			break;
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			SetTextAlign(hdc, TA_CENTER | TA_BASELINE);
			HFONT hFont = CreateFontIndirect(&lf);
			SelectObject(hdc, hFont);
			SetTextColor(hdc, color);
			TextOut(hdc, width / 2, height / 2, str.c_str(), str.size());
			EndPaint(hWnd, &ps);
		}
			break;
		case WM_COMMAND: {
			int id = LOWORD(wParam);
			if (id == CHANGE_COLOR) {
				if (ChooseColor(&cc))
					color = cc.rgbResult;
				InvalidateRect(hWnd, nullptr, true);
			}
			else if (id >= 0 && id < fonts.size()) {
				SetFont(id);
				InvalidateRect(hWnd, nullptr, true);
			}
		} break;
		case WM_CHAR:
			if (wParam == VK_BACK) {
				if (!str.empty()) str.pop_back();
			} else {
				str.push_back(wParam);
			}
			InvalidateRect(hWnd, nullptr, true);
			break;
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
		wc.lpszClassName, L"My first lab",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 900, 400,
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

void AddFonts(HMENU hMenu) {
	for (int i = 0; i < fonts.size(); ++i)
		AppendMenuW(hMenu, MF_STRING, i, fonts[i]);
}

void AddMenu(HWND hwnd) {
	HMENU hMenuBar = CreateMenu();

	HMENU hMenuFont = CreateMenu(); 
	AddFonts(hMenuFont);

	AppendMenuW(hMenuBar, MF_STRING, CHANGE_COLOR, L"Выбрать цвет");
	AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hMenuFont, L"Выбрать шрифт");

	SetMenu(hwnd, hMenuBar);
}
