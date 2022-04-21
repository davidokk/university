#pragma once

#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <cmath>
#include <fstream>

struct KPoint { int x, y; };

void Line(HDC hDc, int x0, int y0, int x, int y);
void Line(HDC hDc, KPoint a, KPoint b);

class KShape {
public:
	KShape(HWND hwnd, KPoint center) : hdc(GetDC(hwnd)), c(center) {}
	virtual ~KShape() {}

	void Show() { SelectPen(hdc, GetStockPen(BLACK_PEN)); is_visible = true; Draw(); }
	void Hide() { SelectPen(hdc, GetStockPen(WHITE_PEN)); is_visible = false;  Draw(); }

	void Rotate(double angle_) { bool v = is_visible; Hide(); angle += angle_; if (v) Show(); }
	virtual void Draw() = 0;

protected:
	void FSetTransform();

protected:
	HDC hdc;
	const KPoint c;

	bool is_visible = false;
	double angle = 0;
};

class KPyramid : public KShape {
public:
	KPyramid(HWND hwnd, int x, int y, int rows, int r, COLORREF color)
		: KShape(hwnd, { x, y }), rows(rows), r(r), total((1 + rows)* rows / 2), color(color) {
		int k = 1;
		for (int i = 1; i <= rows; k += ++i) 
			border.push_back(k);
		k = total;
		for (int i = 0; i < rows - 1; i++)
			border.push_back(--k);
		for (int i = rows - 1; i > 1; i--) 
			border.push_back(k -= i);
	}

	~KPyramid() { Hide(); }

	virtual void Draw() override {
		FSetTransform();
		SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));
		for (int i = 1; i <= total; i++) {
			Connect(i, i + getRowAndCol(i).first);
			Connect(i, i + getRowAndCol(i).first + 1);
		}
		for (int i = 1; i <= total; i++) 
			DrawCircle({ getX(i), getY(i) }, r);
		
		if (!border.empty() && border[active] != 0) {
			HBRUSH hColor = CreateSolidBrush(is_visible ? color : RGB(255, 255, 255));
			SelectObject(hdc, hColor);
			DrawCircle({ getX(border[active]), getY(border[active]) }, 1.3 * r);
			DeleteObject(hColor);
		}
	}

	void ChangeActive() {
		Hide();
		if (border.empty())
			active = 0;
		else
			active = (active + 1) % (border.size());
		Show();
	}

private:
	void Connect(int L, int R) {
		if (getRowAndCol(L).first == rows)
			return;
		int a = getX(L), b = getY(L);
		int x = getX(R), y = getY(R);
		Line(hdc, a, b, x, y);	
	}
	void DrawCircle(KPoint k, int r) { Ellipse(hdc, k.x + r, k.y + r, k.x - r, k.y - r); }
	
	std::pair<int, int> getRowAndCol(int num) {
		int k = 0; int i = 1;
		for (i = 1; k < num; k += i++);
		return { i - 1, i - k % num - 1 };
	}
	int getY(int num) {
		int row = getRowAndCol(num).first;
		int height = rows * 2 * r + step * (rows - 1);
		return height / 2 - r - (row - 1) * 2 * r - (row - 1) * step;
	}
	int getX(int num) {
		auto [row, col] = getRowAndCol(num);
		int width = row * 2 * r + step_x * (row - 1);
		return -width / 2 + r + (col - 1) * 2 * r + (col - 1) * step_x;
	}

private:
	int active = 0;

	const int rows, r;
	const int total;

	const COLORREF color;

	const int step = 5;
	const int step_x = 50;

	std::vector<int> border;
};

void KShape::FSetTransform() {
	XFORM m_xm = { 1,0,0,1,0,0 };

	SetMapMode(hdc, MM_ANISOTROPIC);
	SetWindowExtEx(hdc, 1, 1, NULL);
	SetWindowOrgEx(hdc, 0, 0, NULL);

	SetViewportExtEx(hdc, 1, -1, NULL);

	SetViewportOrgEx(hdc, c.x, c.y, NULL);

	SetGraphicsMode(hdc, GM_ADVANCED);

	double anglex = -angle;

	double rad = anglex * (3.141592653589793116 / 180);
	m_xm.eM11 = (FLOAT)cos(rad);
	m_xm.eM12 = (FLOAT)sin(rad);
	m_xm.eM21 = -m_xm.eM12;
	m_xm.eM22 = m_xm.eM11;
	m_xm.eDx = 0;
	m_xm.eDy = 0;

	SetWorldTransform(hdc, &m_xm);
}

void Line(HDC hDc, int x0, int y0, int x, int y) {
	MoveToEx(hDc, x0, y0, nullptr);
	LineTo(hDc, x, y);
}

void Line(HDC hDc, KPoint a, KPoint b) { Line(hDc, a.x, a.y, b.x, b.y); }
