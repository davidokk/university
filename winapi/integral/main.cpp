#include <windows.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include <CommCtrl.h>
#include <winuser.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <tuple>

#pragma comment(lib, "ComCtl32.Lib")

#define IDM_EXIT 2
#define IDM_BTN_DOWN 4
#define IDM_EDIT 5
#define IDM_FUNC_SQUARE 6
#define IDM_FUNC_CUBE 7
#define IDM_FUNC_MODULE 8
#define IDM_FUNC_SIN 9
#define IDM_FUNC_COS 10
#define IDM_START 11
#define IDM_LEFT_BTN 12
#define IDM_EDIT_LEFT 13
#define IDM_RIGHT_BTN 14
#define IDM_EDIT_RIGHT 15
#define ID_STATUSBAR 16
#define IDM_RESTART 17

//прототип функции окна, которая будет определена ниже
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//виды функций
double SquareFunc(double x) { return x * sin(x); }
double CubeFunc(double x) { return x * x * x; }
double ModuleFunc(double x) { return abs(x); }

HMENU hMenubar;
HWND StatusBar;

char szProgName[] = "Integral";

HINSTANCE hinst;

void CreateMenu(HWND);

BOOL Line(HDC hdc, int x1, int y1, int x2, int y2) {
  MoveToEx(hdc, x1, y1, NULL);
  return LineTo(hdc, x2, y2);
}

struct Limits {
  double x_l;
  double x_r;
  Limits() : x_l(-3), x_r(3) {}
};

Limits lim;

std::pair<double, int> Simpson(double a, double b, double(*f)(double c), double accuracy) {
  int n = 2;
  double h = (b - a) / 2;
  double s1, s2, s4, s, ss;
  s1 = h * (f(a) + f(b));
  s2 = 0;
  s4 = 4 * h * f(a + h);
  s = s1 + s2 + s4;
  do {
    ss = s;
    n *= 2;
    h /= 2;
    s1 /= 2;
    s2 = s2 / 2 + s4 / 4;
    s4 = 0;
    for (int i = 1; i <= n; i += 2)
      s4 += f(a + i * h);
    s4 *= 4 * h;
    s = s1 + s2 + s4;
  } while (abs(s - ss) >= accuracy);
  return {s / 3, n};
}

//рисуем функцию
void DrawFunction(HWND hwnd,
//double DrawFunction(HWND hwnd,
                    HDC hdc,
                    double scale,
                    double (* f)(double c),
                    double x_l,
                    double x_r,
                    int n_integral) {
  RECT rect;
  GetClientRect(hwnd, &rect);
  const int xVE = rect.right - rect.left;
  const int yVE = rect.bottom - rect.top;

  int xPixelsPerOne =
      xVE / (scale * 10);
  int yPixelsPerOne = yVE / (scale * 10);
  SetMapMode(hdc, MM_ISOTROPIC);
  SetWindowExtEx(hdc, xVE, yVE, NULL);
  SetViewportExtEx(hdc,
                   (rect.right - rect.left) * 2 / 3,
                   -(rect.bottom - rect.top) * 2 / 3,
                   nullptr); //Определяем облась вывода
  SetViewportOrgEx(hdc,
                   (rect.right - rect.left) * 2 / 3,
                   (rect.bottom - rect.top) / 2,
                   nullptr); //Начало координа


  const int xMin = -xVE * 2 / 5;
  const int xMax = xVE * 2 / 5;
  const int yMin = -yVE * 2 / 3;
  const int yMax = yVE * 2 / 3;

  // Сетка
  HPEN hPen0 = CreatePen(PS_SOLID, 1, 0x808080);
  HPEN hOldPen = (HPEN) SelectObject(hdc, hPen0);
  for (int i = 0; i < xMax; i += xPixelsPerOne * scale / 2) {
    Line(hdc, i, yMax, i, yMin);//ось У
    Line(hdc, -i, yMax, -i, yMin);//ось У
  }
  for (int i = 0; i < yMax; i += yPixelsPerOne * scale / 2) {
    Line(hdc, xMin, i, xMax, i);//ось Х
    Line(hdc, xMin, -i, xMax, -i);//ось Х
  }
  DeleteObject(hPen0);

  HPEN hPen =
      CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // todo цвет будет вводитья в меню
  SelectObject(hdc, hPen);
  //Оси
  MoveToEx(hdc, 0, yMin, NULL);
  LineTo(hdc, 0, yMax);
  LineTo(hdc, 5, yMax - 10);
  MoveToEx(hdc, 0, yMax, NULL);
  LineTo(hdc, -5, yMax - 10);

  MoveToEx(hdc, xMin, 0, NULL);
  LineTo(hdc, xMax, 0);
  LineTo(hdc, xMax - 10, 5);
  MoveToEx(hdc, xMax, 0, NULL);
  LineTo(hdc, xMax - 10, -5);
  SetBkMode(hdc, GEO_PARENT);
  TextOut(hdc, -25, yMax + 10, "y", 1);
  TextOut(hdc, xMax - 10, 30, "x", 1);

  //График
  hPen =
      CreatePen(PS_SOLID,
                3,
                RGB(255, 0, 0)); // todo цвет будет вводитья в меню
  SelectObject(hdc, hPen);
  bool first = true;
  for (double i = -100; i < 100; i += 0.1) {
    if (abs(f(i)) * yPixelsPerOne < yMax && abs(i) * xPixelsPerOne < xMax) {
      if (first) {
        MoveToEx(hdc,
                 (int) (i * xPixelsPerOne),
                 (int) (f(i) * yPixelsPerOne),
                 nullptr);
        first = false;
      } else {
        LineTo(hdc, (int) (i * xPixelsPerOne), (int) (f(i) * yPixelsPerOne));
      }
    }
  }

  //Делаем перо снова чёрным
  hPen = CreatePen(0, 1, RGB(0, 0, 0));
  SelectObject(hdc, hPen);

//Наносим деления
  Line(hdc, 0, 3, 0, -3);
  TextOut(hdc, -5, -5, "0", 1);

  for (int i = xPixelsPerOne * scale; i <= xMax; i += scale * xPixelsPerOne) {
    Line(hdc, i, 3, i, -3);
    Line(hdc, -i, 3, -i, -3);

    TextOut(hdc,
            i - 5,
            -5,
            std::to_string(i / xPixelsPerOne).c_str(),
            std::to_string(i / xPixelsPerOne).length());

    TextOut(hdc,
            -i - 5,
            -5,
            ("-" + std::to_string(i / xPixelsPerOne)).c_str(),
            std::to_string(i / xPixelsPerOne).length() + 1);
  }
  for (int i = yPixelsPerOne * scale; i <= yMax; i += scale * yPixelsPerOne) {
    Line(hdc, -3, i, 3, i);
    Line(hdc, -3, -i, 3, -i);

    TextOut(hdc,
            -5,
            i + 10,
            std::to_string(i / yPixelsPerOne).c_str(),
            std::to_string(i / yPixelsPerOne).length());
    TextOut(hdc,
            -5,
            -i + 10,
            ("-" + std::to_string(i / yPixelsPerOne)).c_str(),
            std::to_string(i / yPixelsPerOne).length() + 1);
  }
  // рассчет интеграла
  HBRUSH hBrush = CreateHatchBrush(HS_FDIAGONAL, RGB(0, 50, 0));
  SelectObject(hdc, hBrush);
  POINT poly_trap[4];
  static double p_x_l;
  static double p_x_r;
  if (p_x_l >= 0) {
    if (x_l > 4 * scale) {
      p_x_l = 4 * scale;
    } else {
      p_x_l = x_l;
    }
  } else {
    if (x_l >= -4 * scale) {
      p_x_l = x_l;
    } else {
      p_x_l = -4 * scale;
    }
  }
  if (p_x_r >= 0) {
    if (x_r > 4 * scale) {
      p_x_r = 4 * scale;
    } else {
      p_x_r = x_r;
    }
  } else {
    if (x_r >= -4 * scale) {
      p_x_r = x_r;
    } else {
      p_x_r = -4 * scale;
    }
  }
  double intgStep = (x_r - x_l) / n_integral;
  double p_intgStep = (p_x_r - p_x_l) / n_integral;
  double Intg_result = (f(x_l) - f(x_r)) / 2;
  for (int i = 0; i < n_integral; i++) {
    Intg_result = Intg_result + abs(f(x_l + intgStep * (i + 1)));
    double begin_x = (p_x_l + p_intgStep * i);
    double end_x = (p_x_l + p_intgStep * (i + 1));
    double begin_y = f(begin_x);
    double end_y = (f(end_x));
    if (end_y <= 6.5 * scale && begin_y <= 6.5 * scale) {
      poly_trap[0] = {(int) (begin_x * xPixelsPerOne), 0};
      poly_trap[1] = {(int) (begin_x * xPixelsPerOne),
                      (int) (begin_y * yPixelsPerOne)};
      poly_trap[2] = {(int) (end_x * xPixelsPerOne),
                      (int) (end_y * yPixelsPerOne)};
      poly_trap[3] = {(int) (end_x * xPixelsPerOne), 0};
      Polygon(hdc, poly_trap, 4);
    } else {
      bool begin = false;
      bool end = false;
      if (begin_y > 6.5) {
        begin = true;
      }
      if (end_y > 6.5) {
        end = true;
      }
      poly_trap[0] = {(int) (begin_x * xPixelsPerOne), 0};
      if (begin) {
        poly_trap[1] = {(int) (begin_x * xPixelsPerOne),
                        (int) (6.5 * scale * yPixelsPerOne)};
      } else {
        poly_trap[1] = {(int) (begin_x * xPixelsPerOne),
                        (int) (begin_y * yPixelsPerOne)};
      }
      if (end) {
        poly_trap[2] = {(int) (end_x * xPixelsPerOne),
                        (int) (6.5 * scale * yPixelsPerOne)};
      } else {
        poly_trap[2] = {(int) (end_x * xPixelsPerOne),
                        (int) (end_y * yPixelsPerOne)};
      }
      poly_trap[3] = {(int) (end_x * xPixelsPerOne), 0};
      Polygon(hdc, poly_trap, 4);
    }
  }
  Intg_result *= intgStep;
 // return Intg_result;
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine,
                   int nCmdShow) {
  HWND hWnd;
  MSG msg;
  WNDCLASS w; //создаём экземпляр структуры WNDCLASS

//И начинаем её заполнять
  w.lpszClassName = szProgName; //имя программы - объявлено выше
  w.hInstance = hInstance; //идентификатор текущего приложения
  w.lpfnWndProc = WndProc; //указатель на функцию окна
  w.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  w.hCursor = LoadCursor(NULL, IDC_ARROW);
  w.lpszMenuName = nullptr; //и меню пока не будет
  //w.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH); //цвет фона окна
  w.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); //цвет фона окна
  w.style = CS_HREDRAW | CS_VREDRAW; //стиль - перерисовываемое по х и по у
  w.cbClsExtra = 0;
  w.cbWndExtra = 0;
  w.lpszMenuName = nullptr;

//Если не удалось зарегистрировать класс окна - выходим
  if (!RegisterClass(&w))
    return 0;

//Создадим окно в памяти, заполнив аргументы CreateWindow
  hWnd = CreateWindow(szProgName, //Имя программы
                      "Computing of integral", //Заголовок окна
                      WS_OVERLAPPEDWINDOW, //Стиль окна - перекрывающееся
                      260, //положение окна на экране по х
                      15, //положение по у
                      800, //ширина
                      650, //высота
                      HWND_DESKTOP, //идентификатор родительского окна
                      (HMENU) nullptr, //идентификатор меню
                      (HINSTANCE) hInstance, //идентификатор экземпляра программы
                      (HINSTANCE) nullptr); //отсутствие дополнительных параметров

//Выводим окно из памяти на экран
  ShowWindow(hWnd, nCmdShow);

//Обновим содержимое окна
  UpdateWindow(hWnd);

//Цикл обработки сообщений

  while (GetMessage(&msg, nullptr, 0, 0)) { //Получаем сообщение из очереди
    TranslateMessage(&msg); //Преобразует сообщения клавиш в символы
    DispatchMessage(&msg); //Передаёт сообщение соответствующей функции окна
  }
  return msg.wParam;
}

//Функция окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
                         WPARAM wParam, LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  static OPENFILENAME ofn;
  static OPENFILENAME sfn;

  HWND hwndButton;
  HWND StartButton;
  HWND RestartButton;
  HWND hEdit;
  HWND EditLeft;
  HWND LeftLimitButton;
  HWND EditRight;
  HWND RightLimitButton;

  char c[100] = "1";
  static double (* f)(double) = SquareFunc;
  RECT rect;
  GetClientRect(hWnd, &rect);
  int cx = rect.right - rect.left;
  int cy = rect.bottom - rect.top;
  static double scale = atoi(c);
  int Status[3];
  static int n_integral = 2;
  static double accuracy = 0.1;
  static double integral = 0.0;
  TCHAR szFileOpen[MAX_PATH];
  static HANDLE hFile;
  static char function[6] = {"x^2"};
  switch (messg) {
    case WM_CREATE:
      CreateMenu(hWnd);
      CheckMenuRadioItem(GetSubMenu(GetMenu(hWnd), 1),
                         IDM_FUNC_SQUARE,
                         IDM_FUNC_COS,
                         IDM_FUNC_SQUARE,
                         MF_BYCOMMAND);
      StatusBar = CreateWindow(STATUSCLASSNAME,
                               "",
                               WS_CHILD | WS_VISIBLE | WS_BORDER
                                   | SBARS_SIZEGRIP | CCS_BOTTOM,
                               0,
                               0,
                               0,
                               0,
                               hWnd,
                               (HMENU) ID_STATUSBAR,
                               hinst,
                               NULL);
      hwndButton = CreateWindow("button",  // Predefined class; Unicode assumed
                                "OK",      // Button text
                                WS_VISIBLE | WS_CHILD,  // Styles
                                cx / 5,         // x position
                                cy / 4,         // y position
                                60,        // Button width
                                30,        // Button height
                                hWnd,     // Parent window
                                (HMENU) IDM_BTN_DOWN,       // No menu.
                                nullptr,
                                nullptr);      // Pointer not needed.
      hEdit = CreateWindow("Edit",  // Predefined class; Unicode assumed
                           "1",      // Button text
                           WS_VISIBLE | WS_CHILD | ES_RIGHT | WS_BORDER
                               | ES_NUMBER,  // Styles
                           cx / 10,         // x position
                           cy / 4,         // y position
                           60,        // Button width
                           30,        // Button height
                           hWnd,     // Parent window
                           (HMENU) IDM_EDIT,       // No menu.
                           nullptr,
                           nullptr);      // Pointer not needed.
      LeftLimitButton =
          CreateWindow("button",  // Predefined class; Unicode assumed
                       "Left",      // Button text
                       WS_VISIBLE | WS_CHILD,  // Styles
                       cx / 5,         // x position
                       cy * 5 / 9,         // y position
                       60,        // Button width
                       30,        // Button height
                       hWnd,     // Parent window
                       (HMENU) IDM_LEFT_BTN,       // No menu.
                       nullptr,
                       nullptr);      // Pointer not needed.
      EditLeft =
          CreateWindow(TEXT("Edit"),  // Predefined class; Unicode assumed
                       "-3",      // Button text
                       WS_VISIBLE | WS_CHILD | ES_RIGHT | WS_BORDER,  // Styles
                       cx / 10,         // x position
                       cy * 5 / 9,         // y position
                       60,        // Button width
                       30,        // Button height
                       hWnd,     // Parent window
                       (HMENU) IDM_EDIT_LEFT,       // No menu.
                       nullptr,
                       nullptr);      // Pointer not needed.
      RightLimitButton =
          CreateWindow("button",  // Predefined class; Unicode assumed
                       "Right",      // Button text
                       WS_VISIBLE | WS_CHILD,  // Styles
                       cx / 5,         // x position
                       cy * 6 / 9,         // y position
                       60,        // Button width
                       30,        // Button height
                       hWnd,     // Parent window
                       (HMENU) IDM_RIGHT_BTN,       // No menu.
                       nullptr,
                       nullptr);      // Pointer not needed.
      EditRight =
          CreateWindow(TEXT("Edit"),  // Predefined class; Unicode assumed
                       "3",      // Button text
                       WS_VISIBLE | WS_CHILD | ES_RIGHT | WS_BORDER,  // Styles
                       cx / 10,         // x position
                       cy * 6 / 9,         // y position
                       60,        // Button width
                       30,        // Button height
                       hWnd,     // Parent window
                       (HMENU) IDM_EDIT_RIGHT,       // No menu.
                       nullptr,
                       nullptr);      // Pointer not needed.
      StartButton = CreateWindow("button",  // Predefined class; Unicode assumed
                                 "+accuracy",      // Button text
                                 WS_VISIBLE | WS_CHILD,  // Styles
                                 cx / 30,         // x position
                                 cy * 7 / 9,         // y position
                                 100,        // Button width
                                 50,        // Button height
                                 hWnd,     // Parent window
                                 (HMENU) IDM_START,       // No menu.
                                 nullptr,
                                 nullptr);      // Pointer not needed.
      RestartButton =
          CreateWindow("button",  // Predefined class; Unicode assumed
                       "-accuracy",      // Button text
                       WS_VISIBLE | WS_CHILD,  // Styles
                       cx / 5,         // x position
                       cy * 7 / 9,         // y position
                       100,        // Button width
                       50,        // Button height
                       hWnd,     // Parent window
                       (HMENU) IDM_RESTART,       // No menu.
                       nullptr,
                       nullptr);      // Pointer not needed.
      {
        ofn.lStructSize = sizeof(ofn);
        ofn.lpstrFile = szFileOpen;
        ofn.hwndOwner = hWnd;
        ofn.nMaxFile = sizeof(szFileOpen);
        ofn.nFilterIndex = 1;
        ofn.lpstrInitialDir = NULL;
        ofn.lpstrFileTitle = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
      }
      break;

    case WM_PAINT: {
      hdc = BeginPaint(hWnd, &ps);
      SetBkMode(hdc, GEO_PARENT);
      TextOut(hdc,
              cx / 40,
              cy / 6,
              "Zoom in (enter the number of times):",
              36);
      TextOut(hdc,
              cx / 40,
              cy * 6 / 13,
              "Set the limits (enter left and right):",
              38);
      std::tie(integral, n_integral) = Simpson(lim.x_l, lim.x_r, f, accuracy);
      //n_integral /= 2048;
      //integral =
          DrawFunction(hWnd, hdc, scale, f, lim.x_l, lim.x_r, n_integral);
      HDC hDC = BeginPaint(hWnd, &ps);
      RECT rect;
      GetClientRect(hWnd, &rect);
      Status[0] = rect.right / 3;
      Status[1] = Status[0] * 2;
      Status[2] = Status[0] * 3;
      SendMessage(StatusBar, SB_SETPARTS, 3, (LPARAM) Status);
      {
        char output[91];
        sprintf(output, "Function: %s", function);
        SendMessage(StatusBar,
                    SB_SETTEXT,
                    0, (LPARAM) output);
        sprintf(output, "Accuracy %f", accuracy);
        SendMessage(StatusBar,
                    SB_SETTEXT,
                    1,
                    (LPARAM) output);

        sprintf(output, "Integral = %f", integral);
        SendMessage(StatusBar, SB_SETTEXT, 2, (LPARAM) output);
      }
      break;
    }

    case WM_COMMAND:
      switch (LOWORD(wParam)) {
        case IDM_EXIT:
          DestroyWindow(hWnd);
          break;

        case IDM_BTN_DOWN:
          if (scale != 0) {
            InvalidateRect(hWnd,
                           nullptr,
                           true);
          }
          break;
        case IDM_START:
          if (scale != 0) {
            InvalidateRect(hWnd,
                           nullptr,
                           true);
          }
          n_integral *= 2;
          if (abs(accuracy - 0.000001) > exp(-20)) accuracy *= 0.1;
          break;
        case IDM_RESTART:n_integral = 2;
          if (abs(accuracy - 0.1) > exp(-5)) accuracy /= 0.1;
          if (scale != 0) {
            InvalidateRect(hWnd,
                           nullptr,
                           true);
          }
          break;
        case IDM_LEFT_BTN:
          if (scale != 0) {
            InvalidateRect(hWnd,
                           nullptr,
                           true);
          }
          break;
        case IDM_RIGHT_BTN:
          if (scale != 0) {
            InvalidateRect(hWnd,
                           nullptr,
                           true);
          }
          break;
        case IDM_EDIT:
          if (HIWORD(wParam) == EN_UPDATE) {
            GetWindowTextA((HWND) lParam, c, 3);
            scale = atoi(c);
          }
          break;
        case IDM_EDIT_LEFT:
          if (HIWORD(wParam) == EN_UPDATE) {
            GetWindowTextA((HWND) lParam, c, 5);
            lim.x_l = atoi(c);
          }
          break;
        case IDM_EDIT_RIGHT:
          if (HIWORD(wParam) == EN_UPDATE) {
            GetWindowTextA((HWND) lParam, c, 5);
            lim.x_r = atoi(c);
          }
          break;
        case IDM_FUNC_SQUARE:f = SquareFunc;
          InvalidateRect(hWnd,
                         nullptr,
                         true);
          for (int i{0}; i < 6; ++i) {
            function[i] = ' ';
          }
          function[0] = 'x';
          function[1] = '^';
          function[2] = '2';
          CheckMenuRadioItem(GetSubMenu(GetMenu(hWnd), 1), IDM_FUNC_SQUARE,
                             IDM_FUNC_COS, IDM_FUNC_SQUARE, MF_BYCOMMAND);
          break;
        case IDM_FUNC_CUBE:f = CubeFunc;
          InvalidateRect(hWnd,
                         nullptr,
                         true);
          for (int i{0}; i < 6; ++i) {
            function[i] = ' ';
          }
          function[0] = 'x';
          function[1] = '^';
          function[2] = '3';
          CheckMenuRadioItem(GetSubMenu(GetMenu(hWnd), 1), IDM_FUNC_SQUARE,
                             IDM_FUNC_COS, IDM_FUNC_CUBE, MF_BYCOMMAND);
          break;
        case IDM_FUNC_MODULE:f = ModuleFunc;
          InvalidateRect(hWnd,
                         nullptr,
                         true);
          for (int i{0}; i < 6; ++i) {
            function[i] = ' ';
          }
          function[0] = '|';
          function[1] = 'x';
          function[2] = '|';
          CheckMenuRadioItem(GetSubMenu(GetMenu(hWnd), 1), IDM_FUNC_SQUARE,
                             IDM_FUNC_COS, IDM_FUNC_MODULE, MF_BYCOMMAND);
          break;
        case IDM_FUNC_SIN:f = sin;
          InvalidateRect(hWnd,
                         nullptr,
                         true);
          for (int i{0}; i < 6; ++i) {
            function[i] = ' ';
          }
          function[0] = 's';
          function[1] = 'i';
          function[2] = 'n';
          function[3] = '(';
          function[4] = 'x';
          function[5] = ')';
          CheckMenuRadioItem(GetSubMenu(GetMenu(hWnd), 1), IDM_FUNC_SQUARE,
                             IDM_FUNC_COS, IDM_FUNC_SIN, MF_BYCOMMAND);
          break;
        case IDM_FUNC_COS:f = cos;
          InvalidateRect(hWnd,
                         nullptr,
                         true);
          for (int i{0}; i < 6; ++i) {
            function[i] = ' ';
          }
          function[0] = 'c';
          function[1] = 'o';
          function[2] = 's';
          function[3] = '(';
          function[4] = 'x';
          function[5] = ')';
          CheckMenuRadioItem(GetSubMenu(GetMenu(hWnd), 1), IDM_FUNC_SQUARE,
                             IDM_FUNC_COS, IDM_FUNC_COS, MF_BYCOMMAND);
          break;
        default:break;
      }
      break;

    case WM_SIZE:SendMessage(GetDlgItem(hWnd, ID_STATUSBAR), WM_SIZE, 0, 0);
      break;

    case WM_DESTROY:PostQuitMessage(0); //Посылаем сообщение выхода с кодом 0 - нормальное завершение
      break;

    default:
      return (DefWindowProc(hWnd,
                            messg,
                            wParam,
                            lParam)); //освобождаем очередь приложения от нераспознаных
  }
  return 0;
}

void CreateMenu(HWND hWnd) {
  hMenubar = CreateMenu();
  HMENU hFile = CreateMenu();

  static HMENU hFunction = CreateMenu();
  AppendMenu(hMenubar, MF_POPUP, (UINT_PTR) hFile, "File");

  AppendMenu(hFile, MF_STRING, IDM_EXIT, "Exit");

  AppendMenu(hMenubar, MF_POPUP, (UINT_PTR) hFunction, "Function");

  AppendMenu(hFunction, MFT_RADIOCHECK, IDM_FUNC_SQUARE, "x^2");
  AppendMenu(hFunction, MFT_RADIOCHECK, IDM_FUNC_CUBE, "x^3");
  AppendMenu(hFunction, MFT_RADIOCHECK, IDM_FUNC_MODULE, "|x|");
  AppendMenu(hFunction, MFT_RADIOCHECK, IDM_FUNC_SIN, "sin(x)");
  AppendMenu(hFunction, MFT_RADIOCHECK, IDM_FUNC_COS, "cos(x)");

  SetMenu(hWnd, hMenubar);
}
