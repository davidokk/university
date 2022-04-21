#include "MVC.h"

#include <string>

void SetModel::Accept(Visitor* v) { v->Visit(*this); }

void SetModel::Add(int val) { 
	while (val >= capacity)
		Expand();
	data[val] = true;
	max_elem = max(max_elem, val);
	Notify();
}

int SetModel::Cardinality() {
	int ans = 0;
	auto it = CreateIterator();
	while (!it->IsDone()) {
		ans += it->CurrentItem();
		it->Next();
	}
	return ans;
}

void SetModel::Expand() {
	bool* new_data = NewArray(capacity * 2);
	for (int i = 0; i < capacity; ++i)
		new_data[i] = data[i];
	delete[] data;
	data = new_data;
	capacity *= 2;
}

bool* SetModel::NewArray(int size) {
	bool* data1 = new bool[size];
	for (int i = 0; i < size; i++)
		data1[i] = false;
	return data1;
}

View::View(HWND wnd, SetModel* m) : hWnd(wnd), model(m) {
	model->Attach(this);

	hAddButton = CreateWindow(
		L"button", L"Добавить", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		130, 310, 190, 30,
		hWnd, (HMENU)IDB_ADD_BUTTON, NULL, NULL
	);
	hChangeViewButton = CreateWindow(
		L"button", L"Изменить вид", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		500, 310, 190, 30,
		hWnd, (HMENU)IDB_CHANGE_VIEW, NULL, NULL
	);
	hSaveButton = CreateWindow(
		L"button", L"Сохранить", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		350, 400, 190, 30,
		hWnd, (HMENU)IDB_SAVE_BUTTON, NULL, NULL
	);
	hEdit = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_NUMBER,
		130, 270, 190, 30,
		hWnd, (HMENU)IDB_EDIT, NULL, NULL
	);
}

void View::Update() {
	InvalidateRect(hWnd, nullptr, true);
	SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(L""));
	PAINTSTRUCT ps;
	hDc = BeginPaint(hWnd, &ps);
	PrintModel();
	PrintCardinality();
	EndPaint(hWnd, &ps);
}

void View::PrintModel() {
	SetTextAlign(hDc, TA_CENTER | TA_BASELINE);
	TextOut(hDc, 85, 100, L"Множество:", 10);
	int x = 125;
	int a = 40;
	auto it = realView ? model->CreateIterator() : model->CreateSmartIterator();
	while (!it->IsDone()) {
		std::wstring str = std::to_wstring(it->CurrentItem());
		Rectangle(hDc, x, 100 - a / 2, x + a, 100 + a / 2);
		TextOut(hDc, x + a / 2, 100, str.c_str(), str.size());
		x += a;
		it->Next();
	}
}

void View::PrintCardinality() {
	std::wstring mx = std::to_wstring(model->Cardinality());
	TextOut(hDc, 130, 200, L"Cardinality:", 12);
	TextOut(hDc, 200, 200, mx.c_str(), mx.size());
}

int View::GetEditValue() const {
	char* str = new char[10];
	GetWindowTextA(hEdit, str, 10);
	if (std::string(str).empty())
		return 0;
	return std::stoi(std::string(str));
}
