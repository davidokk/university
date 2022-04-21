#pragma once

#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <cmath>
#include <fstream>

struct KPoint {
	int x, y;
	void Shift(int dx, int dy) { x += dx; y += dy; }
};

void Line(HDC hDc, int x0, int y0, int x, int y);
void Line(HDC hDc, KPoint a, KPoint b);

KPoint InProportion(KPoint l, KPoint r, double k);
KPoint Center(KPoint l, KPoint r);

double DegToRad(int angle);
KPoint PLengthAngle(KPoint p, int lenght, double angl);

class KShape {
public:
	KShape(HWND hwnd, KPoint center) : hdc(GetDC(hwnd)), c(center) {}
	virtual ~KShape() {}

	void Show() { SelectPen(hdc, GetStockPen(BLACK_PEN)); is_visible = true; Draw(); }
	void Hide() { SelectPen(hdc, GetStockPen(WHITE_PEN)); is_visible = false;  Draw(); }
	void ToggleVisible() { is_visible ? Hide() : Show(); }

	void Shift(int dx, int dy) { bool v = is_visible; Hide();  DX += dx; DY += dy; if (v) Show(); }
	void MoveTo(int ax, int ay) { Shift(ax - c.x - DX, ay - c.y - DY); }

	void Rotate(double angle_) { bool v = is_visible; Hide(); angle += angle_; if (v) Show(); }
	void Expand(double coeff_) { bool v = is_visible; Hide(); coeff *= coeff_; if (v) Show(); }

	virtual void Draw() = 0;

	void FSetTransform();
	KPoint Cur(KPoint x) { return InProportion({ c.x + DX, c.y + DY }, { x.x + DX, x.y + DY }, coeff); }

protected:
	HDC hdc;
	const KPoint c;

	bool is_visible = false;
	double angle = 0, coeff = 1;
	int DX = 0, DY = 0;
};

class KCircle : public KShape {
public:
	KCircle(HWND hwnd, int x, int y, int radius) : KShape(hwnd, { x, y }), r(radius) {}

	~KCircle() { Hide(); }

	virtual void Draw() override { FSetTransform(); Ellipse(hdc, -R(), -R(), R(), R()); }

protected:
	const double r;
	double R() { return r * coeff; }
};

class KCustomCircle : public KCircle {
public:
	KCustomCircle(HWND hwnd, int x, int y, int radius) : KCircle(hwnd, x, y, radius) {}

	~KCustomCircle() { Hide(); }

	virtual void Draw() override {
		FSetTransform();
		Ellipse(hdc, -R(), -R(), R(), R()); Ellipse(hdc, -R() / 2, -R() / 2, R() / 2, R() / 2);
		Line(hdc, -R(), 0, R(), 0); Line(hdc, 0, -R(), 0, R());
	}
};

class KParallelogram : public KShape {
public:
	KParallelogram(HWND hwnd, int px, int py, int l1, int l2, double angle_)
		: KParallelogram(hwnd, { px, py }, PLengthAngle({ px, py }, l1, 0), PLengthAngle({ px, py }, l2, angle_)) {}

	~KParallelogram() { Hide(); }

	virtual void Draw() override {
		FSetTransform();
		LineInNew(x, y); LineInNew(y, z); LineInNew(z, t); LineInNew(t, x);
	}

private:
	KParallelogram(HWND hwnd, KPoint p1, KPoint p2, KPoint p3) : KShape(hwnd, Center(p2, p3)),
		x(p1), y(p2), t(p3), z({ 2 * c.x - p1.x, 2 * c.y - p1.y }) {}

protected:
	const KPoint x, y, z, t;

	KPoint WithCenter(KPoint p) { return { p.x - Cur(c).x, p.y - Cur(c).y }; }
	void LineInNew(KPoint a, KPoint b) { Line(hdc, WithCenter(Cur(a)), WithCenter(Cur(b))); }
};

class KParallelogramWithDiagonals : public KParallelogram {
public:
	KParallelogramWithDiagonals(HWND hwnd, int px, int py, int l1, int l2, double angle_)
		: KParallelogram(hwnd, px, py, l1, l2, angle_) {}

	~KParallelogramWithDiagonals() { Hide(); }

	virtual void Draw() override {
		FSetTransform();
		LineInNew(x, y); LineInNew(y, z); LineInNew(z, t); LineInNew(t, x);
		LineInNew(x, z); LineInNew(y, t);
	}
};

class KColoredParallelogram : public KParallelogram {
public:
	typedef COLORREF clr;

	KColoredParallelogram(HWND hwnd, int px, int py, int l1, int l2, double angle_,
						  clr clr1 = 0xc0c0c0, clr clr2 = 0x969696, clr clr3 = 0x808080, clr clr4 = 0x333333) 
		: KParallelogram(hwnd, px, py, l1, l2, angle_), c1(clr1), c2(clr2), c3(clr3), c4(clr4) {}

	~KColoredParallelogram() { Hide(); }

	virtual void Draw() override {FSetTransform(); Fill(!is_visible); }

private:
	void PaintTriangle(KPoint a, KPoint b, KPoint c, COLORREF color) {
		POINT* p = new POINT[3]{ MakePoint(a), MakePoint(b), MakePoint(c) };
		HBRUSH hbrush = CreateSolidBrush(color);
		SelectObject(hdc, hbrush);
		Polygon(hdc, p, 3);
		delete[] p;
		DeleteObject(hbrush);
	}

	void Fill(bool hide) {
		COLORREF white = RGB(255, 255, 255);
		PaintTriangle(x, y, c, hide ? white : c1);
		PaintTriangle(y, z, c, hide ? white : c2);
		PaintTriangle(z, t, c, hide ? white : c3);
		PaintTriangle(t, x, c, hide ? white : c4);
	}

	POINT MakePoint(KPoint p) { p = WithCenter(Cur(p)); return { p.x, p.y }; }

private:
	COLORREF c1, c2, c3, c4; 
};

void KShape::FSetTransform() {
	XFORM m_xm = { 1,0,0,1,0,0 };

	SetMapMode(hdc, MM_ANISOTROPIC);
	SetWindowExtEx(hdc, 1, 1, NULL);
	SetWindowOrgEx(hdc, 0, 0, NULL);

	//SetViewportExtEx(hdc, 1, -1, NULL);
	SetViewportExtEx(hdc, -1, -1, NULL);

	KPoint center = Cur(c);
	SetViewportOrgEx(hdc, center.x, center.y, NULL);

	SetGraphicsMode(hdc, GM_ADVANCED);

	double anglex = -angle;
	//double anglex = angle;

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

KPoint Center(KPoint l, KPoint r) { return { (l.x + r.x) / 2, (l.y + r.y) / 2 }; }

KPoint InProportion(KPoint l, KPoint r, double k) {
	if (k == 1) return r;
	k /= 1 - k;
	return { static_cast<int>((l.x + r.x * k) / (1 + k)), static_cast<int>((l.y + r.y * k) / (1 + k)) };
}

constexpr double PI = 3.14159265358979323846;
double DegToRad(int angle) { return angle * PI / 180; }

KPoint PLengthAngle(KPoint p, int lenght, double angl) {
	angl = DegToRad(angl);
	return { static_cast<int>(p.x + lenght * cos(angl)), static_cast<int>(p.y + lenght * sin(angl)) };
}
