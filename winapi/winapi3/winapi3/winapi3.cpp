#include <iostream>
#include <windows.h>
#include <string>
#include <CommCtrl.h>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>

#include "identifiers.h"
#include "shapes.h"

KPyramid* shape;
int width, height;
int rows = 0, radius = 0, total = 0, active = 0;
COLORREF color = 0;

std::vector<HWND> hButtons;
HWND StatusBar;

int current_input = -1;
wchar_t szDirect[260];
wchar_t szFileName[260];
OPENFILENAME ofn; 

HINSTANCE hinst;

std::string File() {
	std::wstring wstr(szDirect);
	return { wstr.begin(), wstr.end() };
}

std::tuple<int, int, COLORREF> Error(HWND hwnd, std::wstring message = L"Неверный формат файла") {
	if (!message.empty())
		MessageBox(hwnd, message.c_str(), L"Error", MB_ICONSTOP | MB_OK);
	return { 0, 0, 0 };
}

std::tuple<int, int, COLORREF> ReadFile(HWND hwnd) {
	if (GetOpenFileName(&ofn)) {
		std::ifstream input(File());
		std::string type;
		input >> type;
		if (type != "DATA")
			return Error(hwnd);
		int rows, radius;
		input >> rows >> radius;
		input >> type;
		if (type == "RGB") {
			int r, g, b;
			input >> r >> g >> b;
			return { rows, radius, RGB(r, g, b) };
		}
		else {
			int x;
			input >> std::hex >> x;
			return { rows, radius, x };
		}
	}
	return Error(hwnd, L"Не выбран файл");
}

void Dialog(HWND);
void ColorDialog(HWND);
void RegisterDialog();
void RegisterColorDialog();

void AddMenu(HWND);
void AddButtons(HWND);
void AddStatusBar(HWND);
void FillStatusBar();
void ChangeRadio(HWND, int);
int GetEditValue(HWND);

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
	wc.lpszClassName = L"WindowClass";
	wc.lpszMenuName = nullptr;

	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT {
		static PAINTSTRUCT ps;
		switch (uMsg) {
		case WM_SIZE:
			width = LOWORD(lParam);
			height = HIWORD(lParam);
			AddButtons(hWnd);
			SendMessage(GetDlgItem(hWnd, ID_STATUSBAR), WM_SIZE, 0, 0);
			break;
		case WM_CREATE:
			RegisterDialog();
			RegisterColorDialog();
			AddMenu(hWnd);
			AddStatusBar(hWnd);
			FillStatusBar();
			SetTimer(hWnd, TIMER_COLOR, 700, NULL);
			break;
		case WM_TIMER:
			if (wParam == TIMER_ROTATE) {
				shape->Rotate(1);
			} else if (wParam == TIMER_COLOR) {
				shape->ChangeActive();
			}
			break;
		case WM_PAINT:
			BeginPaint(hWnd, &ps);
			delete shape;
			shape = new KPyramid(hWnd, width / 2, height / 2, rows, radius, color);
			shape->Show();
			EndPaint(hWnd, &ps);
			break;
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
			case ON_ROTATE:
				SetTimer(hWnd, TIMER_ROTATE, 40, NULL);
				break;
			case OFF_ROTATE:
				KillTimer(hWnd, TIMER_ROTATE);
				break;
			case ID_READ_FILE: 
				std::tie(rows, radius, color) = ReadFile(hWnd);
				total = rows * (rows + 1) / 2;
				active = 0;
				FillStatusBar();
				ChangeRadio(hWnd, ID_READ_FILE);
				InvalidateRect(hWnd, nullptr, true);
				break;
			case ID_USER_INPUT:
				Dialog(hWnd);
				ChangeRadio(hWnd, ID_USER_INPUT);
				break;
			case UPDATE_PARAMS:
				FillStatusBar();
				InvalidateRect(hWnd, nullptr, true);
				break;
			}
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
		wc.lpszClassName, L"WinApi 3",
		WS_OVERLAPPEDWINDOW,
		100, 100, 1000, 700,
		nullptr, nullptr, hInstance, nullptr
	);

	if (hwnd == INVALID_HANDLE_VALUE) {
		MessageBox(nullptr, L"Ошибка создания окна", L"Ошибка", MB_OK | MB_ICONSTOP);
		return NULL;
	}

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szDirect;
	*(ofn.lpstrFile) = 0;
	ofn.nMaxFile = sizeof(szDirect);
	ofn.lpstrFilter = L"Text Files\0*.txt\0\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = szFileName;
	*(ofn.lpstrFileTitle) = 0;
	ofn.nMaxFileTitle = sizeof(szFileName);
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_EXPLORER;



	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return msg.wParam;
}

void AddMenu(HWND hwnd) {
	HMENU hMenuBar = CreateMenu();
	HMENU hSize = CreateMenu();
	HMENU hRotate = CreateMenu();

	AppendMenuW(hSize, MF_STRING, ID_READ_FILE, L"Считать из файла");
	AppendMenuW(hSize, MF_STRING, ID_USER_INPUT, L"Задать вручную");

	AppendMenuW(hRotate, MF_STRING, ON_ROTATE, L"Включить");
	AppendMenuW(hRotate, MF_STRING, OFF_ROTATE, L"Выключить");

	AppendMenuW(hMenuBar, MF_POPUP, (UINT)hSize, L"Задать размеры");
	AppendMenuW(hMenuBar, MF_POPUP, (UINT)hRotate, L"Вращение");

	SetMenu(hwnd, hMenuBar);
}

void DeleteButtons() {
	for (auto& button : hButtons)
		ShowWindow(button, SW_HIDE);
	hButtons.clear();
}

void AddButtons(HWND hwnd) {
	DeleteButtons();

	hButtons.push_back(
		CreateWindow(L"button", L"Данные из файла",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			width - 160, 10, 150, 40, hwnd, (HMENU)ID_READ_FILE, nullptr, nullptr)
	);
	hButtons.push_back(
		CreateWindow(L"button", L"Вручную",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			width - 160, 40, 150, 40, hwnd, (HMENU)ID_USER_INPUT, nullptr, nullptr)
	);
	ChangeRadio(hwnd, current_input);
}

void ChangeRadio(HWND hwnd, int cur) {
	current_input = cur;
	if (current_input != -1) 
		CheckRadioButton(hwnd, ID_READ_FILE, ID_USER_INPUT, current_input);
}

void AddStatusBar(HWND hwnd) {
	StatusBar = CreateWindow(STATUSCLASSNAME, L"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | SBARS_SIZEGRIP | CCS_BOTTOM,
		0, 0, 0, 0, hwnd, (HMENU)ID_STATUSBAR, nullptr, nullptr);
	int* parts = new int[4]; 
	parts[0] = 150; 
	parts[1] = 2 * parts[0];
	parts[2] = 3 * parts[0];
	parts[3] = 4 * parts[0];
	SendMessage(StatusBar, SB_SETPARTS, 4, (LPARAM)parts);
	delete[] parts;
}

std::wstring COLORREFToHexStr(COLORREF color) {
	std::ostringstream os;
	os << std::hex << color;
	std::string result = "0x" + os.str();
	return { result.begin(), result.end() };
}

void FillStatusBar() {
	std::wstring str = L"Число строк: " + std::to_wstring(rows);
	SendMessage(StatusBar, SB_SETTEXT, 0, (LPARAM)str.c_str());
	str = L"Радиус: " + std::to_wstring(radius);
	SendMessage(StatusBar, SB_SETTEXT, 1, (LPARAM)str.c_str());
	str = L"Всего шаров: " + std::to_wstring(total);
	SendMessage(StatusBar, SB_SETTEXT, 2, (LPARAM)str.c_str());
	str = L"Цвет: " + COLORREFToHexStr(color);
	SendMessage(StatusBar, SB_SETTEXT, 3, (LPARAM)str.c_str());
}

int GetEditValue(HWND edit) {
	char* str = new char[10];
	GetWindowTextA(edit, str, 10);
	if (std::string(str).empty())
		return 0;
	return std::stoi(std::string(str));
}

std::vector<HWND> dialogWindows;

void DialogButtons(HWND hwnd) {
	dialogWindows.clear();
	HDC hdc = GetDC(hwnd);
	SetTextAlign(hdc, TA_CENTER | TA_BASELINE);
	SetBkMode(hdc, TRANSPARENT);

	TextOut(hdc, 200, 50, L"Количество строк", 16);
	dialogWindows.push_back(CreateWindow(
		L"edit", std::to_wstring(rows).c_str(), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_CENTER,
		160, 60, 80, 22,
		hwnd, (HMENU)DIALOG_LINES, nullptr, nullptr
	));

	TextOut(hdc, 200, 112, L"Радиус окружностей", 18);
	dialogWindows.push_back(CreateWindow(
		L"edit", std::to_wstring(radius).c_str(), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_CENTER,
		160, 122, 80, 22,
		hwnd, (HMENU)DIALOG_RADIUS, nullptr, nullptr
	));

	TextOut(hdc, 200, 174, L"Цвет", 4);
	SendMessage(hwnd, WM_COMMAND, DRAW_RECT, 0);

	dialogWindows.push_back(CreateWindow(
		L"button", L"Выбрать цвет", WS_VISIBLE | WS_CHILD,
		200 - 10 - 120, 224, 120, 40,
		hwnd, (HMENU)CHANGE_COLOR_STANDART, nullptr, nullptr
	));

	dialogWindows.push_back(CreateWindow(
		L"button", L"RGB", WS_VISIBLE | WS_CHILD,
		200 + 10, 224, 120, 40,
		hwnd, (HMENU)CHANGE_COLOR_USER, nullptr, nullptr
	));

	dialogWindows.push_back(CreateWindow(
		L"button", L"OK", WS_VISIBLE | WS_CHILD,
		170, 300, 60, 30,
		hwnd, (HMENU)DIALOG_OK, nullptr, nullptr
	));
}

HWND parent;
void EndDialog(HWND hwnd) {
	rows = GetEditValue(dialogWindows[0]);
	radius = GetEditValue(dialogWindows[1]);
	total = rows * (rows + 1) / 2; active = 0;
	DestroyWindow(hwnd);
	SendMessage(parent, WM_COMMAND, UPDATE_PARAMS, 0);
}

DWORD dColors[3] = { 0, 0, 0 };

void RegisterDialog() {
	WNDCLASSEXW wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT {
		PAINTSTRUCT ps;

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
		case WM_PAINT: {
			HDC hdc = GetDC(hWnd);
			BeginPaint(hWnd, &ps);
			DialogButtons(hWnd);
			EndPaint(hWnd, &ps);
		} break;
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
			case DIALOG_OK:
				EndDialog(hWnd);
				break;
			case CHANGE_COLOR_STANDART:
				if (ChooseColor(&cc)) {
					color = cc.rgbResult;
					SendMessage(hWnd, WM_COMMAND, DRAW_RECT, 0);
				} 
				break;
			case CHANGE_COLOR_USER:
				ColorDialog(hWnd);
				break;
			case DRAW_RECT: {
				HBRUSH hBrush = CreateSolidBrush(color);
				HDC hdc = GetDC(hWnd);
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 200 - 10, 184, 200 + 10, 184 + 10 * 2);
				DeleteObject(hBrush);
			} break;
			}
			break;
		case WM_CLOSE:
			EndDialog(hWnd);
			break;
		}
		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	};
	wc.hInstance = hinst;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpszClassName = L"DialogClass";
	RegisterClassExW(&wc);
}

void Dialog(HWND hwnd) {
	parent = hwnd;
	RECT rect; GetWindowRect(hwnd, &rect);
	CreateWindowExW(WS_EX_DLGMODALFRAME | WS_EX_TOPMOST,
		L"DialogClass", L"Задать размеры",
		WS_VISIBLE | WS_SYSMENU | WS_CAPTION, rect.left + 10, rect.top + 60, 400, 400,
		NULL, NULL, NULL, NULL);
}

std::vector<HWND> hTrackBars;
HWND hOkButton;

void AddTrackBars(HWND hwnd) {
	hTrackBars.clear();
	HDC hdc = GetDC(hwnd);
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, 15, 40, L"RED", 3);
	hTrackBars.push_back(CreateWindowEx(
		0, TRACKBAR_CLASS, L"Trackbar control", 
		WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_ENABLESELRANGE,
		10, 60, 200, 30, hwnd, NULL, NULL, NULL
	));
	TextOut(hdc, 15, 100, L"GREEN", 5);
	hTrackBars.push_back(CreateWindowEx(
		0, TRACKBAR_CLASS, L"Trackbar control",
		WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_ENABLESELRANGE,
		10, 120, 200, 30, hwnd, NULL, NULL, NULL
	));
	TextOut(hdc, 15, 160, L"BLUE", 4);
	hTrackBars.push_back(CreateWindowEx(
		0, TRACKBAR_CLASS, L"Trackbar control",
		WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_ENABLESELRANGE,
		10, 180, 200, 30, hwnd, NULL, NULL, NULL
	));
	for (HWND wnd : hTrackBars) {
		SendMessage(wnd, TBM_SETRANGE, (WPARAM)true, (LPARAM)MAKELONG(0, 255));
		SendMessage(wnd, TBM_SETPAGESIZE, 0, (LPARAM)1);
	}
	hOkButton = CreateWindow(
		L"button", L"OK", WS_VISIBLE | WS_CHILD,
		110, 220, 60, 30,
		hwnd, (HMENU)DIALOG_OK, nullptr, nullptr
	);

	SendMessage(hwnd, WM_COMMAND, DRAW_RECT, 0);
}

HWND parentDialog;
void RegisterColorDialog() {
	WNDCLASSEXW wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT {
		PAINTSTRUCT ps;
		switch (uMsg) {
		case WM_PAINT: {
			HDC hdc = GetDC(hWnd);
			BeginPaint(hWnd, &ps);
			AddTrackBars(hWnd);
			EndPaint(hWnd, &ps);
		} break;
		case WM_HSCROLL: {
			color = RGB(SendMessage(hTrackBars[0], TBM_GETPOS, 0, 0),
				SendMessage(hTrackBars[1], TBM_GETPOS, 0, 0),
				SendMessage(hTrackBars[2], TBM_GETPOS, 0, 0));
			SendMessage(hWnd, WM_COMMAND, DRAW_RECT, 0);
		}
			break;
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
			case DIALOG_OK: 
				DestroyWindow(hWnd);
				SendMessage(parentDialog, WM_COMMAND, DRAW_RECT, 0);
				break;
			case DRAW_RECT: {
				HBRUSH hBrush = CreateSolidBrush(RGB(SendMessage(hTrackBars[0], TBM_GETPOS, 0, 0),
					SendMessage(hTrackBars[1], TBM_GETPOS, 0, 0),
					SendMessage(hTrackBars[2], TBM_GETPOS, 0, 0)));
				HDC hdc = GetDC(hWnd);
				SelectObject(hdc, hBrush);
				Rectangle(hdc, 50, 225, 50 + 50, 245);
				DeleteObject(hBrush);
			} break;
			}
			break;
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		}
		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	};
	wc.hInstance = hinst;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpszClassName = L"ColorDialogClass";
	RegisterClassExW(&wc);
}

void ColorDialog(HWND hwnd) {
	parentDialog = hwnd;
	RECT rect; GetWindowRect(hwnd, &rect);
	CreateWindowExW(WS_EX_DLGMODALFRAME | WS_EX_TOPMOST,
		L"ColorDialogClass", L"RGB",
		WS_VISIBLE | WS_SYSMENU | WS_CAPTION, rect.left + 10, rect.top + 60, 245, 330,
		NULL, NULL, NULL, NULL);
}
