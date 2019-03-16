// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw.h"
#include "time.h"
#include "windows.h"


#define MAX_LOADSTRING 100
#define TMR_1 1

// Global Variables:

	HWND tekst;
	HWND inf_waga;
	DWORD dlugosc;
	LPSTR Bufor;
	char bufor_masa[10];

	HWND legenda;
	HWND hwndButton;
	HWND masa_bloku_1;
	HWND masa_bloku_2;

	LPTSTR str;
	PSTR bufor;
	INT wynik;
bool dobrze = false;
bool mozna_generowac = true;
int licznik_g = 0;
	PAINTSTRUCT ps;
	HDC hdc;

HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

INT value;
short pion = 0;
short bok = 0;
short wys = 0;
short szer = 0;
short yp = 0;
short xp = 0;
short masa = 0;
short max_waga = 6400;
RECT obszar = { 250, 122, 510, 330 };
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


void MyOnPaint(HDC hdc)
{
	value++;
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	Pen pen1(Color(255, 200, 200, 0));
	Pen pen2(Color(255, 0, 0, 0));
	SolidBrush brush(Color(255, 100, 100, 100));

	graphics.FillRectangle(&brush, 420 + bok, 122, 40, 8);
	graphics.DrawLine(&pen2, 440 + bok, 130, 440 + bok, 230 + pion);
	graphics.DrawLine(&pen2, 110, 100, 110, 130);
	graphics.DrawLine(&pen2, 120, 100, 120, 130);
	graphics.DrawLine(&pen2, 130, 100, 130, 130);
	graphics.DrawLine(&pen1, 140, 105, 510, 105);
	graphics.DrawLine(&pen1, 140, 125, 520, 125);
	graphics.DrawLine(&pen1, 200, 70, 200, 300);
	graphics.DrawLine(&pen1, 220, 55, 220, 300);
	graphics.DrawRectangle(&pen2, 100, 100, 40, 30);
	graphics.DrawRectangle(&pen2, 180, 290, 60, 20);

	graphics.DrawRectangle(&pen2, xp, yp, szer, wys);

	graphics.DrawLine(&pen2, 180, 300, 240, 300);
	for (int i = 0; i < 14; i++)
	{
		graphics.DrawLine(&pen1, 200, 280 - 15 * i, 220, 265 - 15 * i);
		graphics.DrawLine(&pen1, 200, 265 - 15 * i, 220, 265 - 15 * i);
	}
	graphics.DrawLine(&pen1, 200, 70, 220, 55);
	for (int i = 0; i < 19; i++)
	{
		graphics.DrawLine(&pen1, 140 + 20 * i, 125, 150 + 20 * i, 105);
		graphics.DrawLine(&pen1, 150 + 20 * i, 105, 160 + 20 * i, 125);
	}
	graphics.DrawLine(&pen2, 140, 105, 220, 55);
	graphics.DrawLine(&pen2, 220, 55, 320, 105);
	graphics.DrawLine(&pen2, 220, 55, 420, 105);
}


int OnCreate(HWND window)
{
	// SetTimer(window, TMR_1, 25, 0);
	return 0;
}


int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	srand(time(NULL));
	value = 10;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	legenda = CreateWindow(TEXT("STATIC"), 
		TEXT("Legenda: \nG - Generowanie bloku\nF - Chwytanie bloku\nQ - Puszczenie bloku\n\nDŸwig unosi elementy które wa¿¹ mniej ni¿ waga ustalona w oknie tekstowym. \nMasa zale¿y od rozmiaru bloku."), 
		WS_VISIBLE | WS_CHILD | WS_BORDER, 650, 100, 300, 150, hWnd, NULL, NULL, NULL);

	inf_waga = CreateWindow(TEXT("Edit"), TEXT("Podaj dopuszczaln¹ wagê"), WS_CHILD | WS_VISIBLE | WS_BORDER, 100, 20, 180, 20, hWnd, NULL, NULL, NULL);
	SetWindowText(inf_waga, (LPSTR)"Podaj maksymalny udzwig");

	

	masa_bloku_1 = CreateWindow(TEXT("Static"), TEXT("Masa bloku"), WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 20, 100, 20, hWnd, NULL, NULL, NULL);
	masa_bloku_2 = CreateWindow(TEXT("Edit"), TEXT("Masa bloku"), WS_CHILD | WS_VISIBLE | WS_BORDER, 400, 20, 50, 20, hWnd, NULL, NULL, NULL);
	
	hwndButton = CreateWindow(TEXT("button"), TEXT("Przypisz UdŸwig"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WM_LBUTTONDOWN, 520, 25, 120, 50, hWnd, (HMENU)ID_BUTTON1, hInstance, NULL);
	OnCreate(hWnd);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

void Rysowanie(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	InvalidateRect(hWnd, &obszar, TRUE);
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint(hdc);
	EndPaint(hWnd, &ps);
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
//	PAINTSTRUCT ps;
//	HDC hdc;
	//OnCreate(hWnd,wParam,lParam);
	//OnTimer(hWnd,wParam,lParam);

	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			if (bok > (-170))	bok -= 2;
			if (dobrze)		xp -= 2;
			if (xp < 250)
			{
				xp = 250;
				bok += 2;
			}
			Rysowanie(hWnd, message, wParam, lParam);
			break;
		case VK_RIGHT:
			if (bok < 50)		bok += 2;
			if (dobrze)		xp += 2;
			if (xp > 430)
			{
				xp = 430;
				bok -= 2;
			}
			Rysowanie(hWnd, message, wParam, lParam); 
			break;
		case VK_UP:
			if (pion > -80)	pion -= 1;
			if (dobrze)		yp -= 1;
			if (yp <= 150)	yp = 150;
			Rysowanie(hWnd, message, wParam, lParam);
			break;
		case VK_DOWN:
			if (pion < 70)	pion += 1;
			if (dobrze)		yp += 1;
			if (yp + wys > 310)
			{
				yp = 310 - wys;
				pion--;
			}
			Rysowanie(hWnd, message, wParam, lParam);
			break;
		case 0x47:																					//G - generowanie
			
			if (mozna_generowac)
			{
				dobrze = false;
				wys = 20 + rand() % 60;
				szer = 20 + rand() % 60;
				yp = 310 - wys;
				xp = 340 + rand() % 120 - szer;
				masa = wys * szer;
				_itoa(masa, bufor_masa, 10);
				LPCSTR pomocniczo = bufor_masa;
				SetWindowText(masa_bloku_2, (LPSTR)pomocniczo);
			}
			else
			{
				licznik_g++;
				if(licznik_g == 1) tekst = CreateWindow(TEXT("Static"), TEXT("Nie mozna wygenerowac"), WS_CHILD | WS_VISIBLE | WS_BORDER, 100, 20, 180, 20, hWnd, NULL, NULL, NULL);
				Rysowanie(hWnd, message, wParam, lParam);	
			}
			Rysowanie(hWnd, message, wParam, lParam);
			break;

		case 0x46:																					//F - ³apanie
			if (440 + bok >= xp && 440 + bok <= xp + szer && 230 + pion >= yp && 230 + pion <= yp + wys && masa <= max_waga) dobrze = true;
			else dobrze = false;
			if (dobrze)
			{
				pion = yp - 230;
				bok = ((xp + xp + szer) / 2) - 440;
				mozna_generowac = false;
			}
			Rysowanie(hWnd, message, wParam, lParam);
			break;

		case 0x51:																				//Q - upuszczanie
			dobrze = false;
			mozna_generowac = true;
			while (yp + wys < 310)
			{
				yp++;
				Rysowanie(hWnd, message, wParam, lParam);
			}
			DestroyWindow(tekst);	
			licznik_g = 0;
			Rysowanie(hWnd, message, wParam, lParam);
			break;
	

		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;		

		default:
			//	value = 0;
			//	KillTimer(hWnd, TMR_1);
			break;
		}
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		case ID_BUTTON1:
			SetFocus(hWnd);
			dlugosc = GetWindowTextLength(inf_waga);
			Bufor = (LPSTR)GlobalAlloc(GPTR, dlugosc + 1);
			GetWindowText(inf_waga, Bufor, dlugosc + 1);
			max_waga = atoi(Bufor);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		MyOnPaint(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TMR_1:
			//force window to repaint
			InvalidateRect(hWnd, NULL, TRUE);
			hdc = BeginPaint(hWnd, &ps);
			MyOnPaint(hdc);
			EndPaint(hWnd, &ps);
			break;
		}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}

	return (INT_PTR)FALSE;
}