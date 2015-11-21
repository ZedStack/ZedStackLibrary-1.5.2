#ifndef ZedStackLibrary
#define ZedStackLibrary

// Library that is being defined:
#include "../.hpp/ZedStack.hpp"

// Needed libraries:
#include <iostream>
#include <sstream>
#include <windows.h>
#include <queue>
#include <process.h>

// Extra libraries int the proyect:
// TODO: Add resting libraries.

/**  G L O B A L   V A R I A B L E S  **/
HWND            hWindow;										// Main screen.
HBITMAP         hBitmap;										// Bitmap of the screen.
HDC             hDeviceContext	= NULL;							// Device context.
LPCSTR          lpcTitle		= "ZedStack Library Project";	// Title of the window.
std::queue<int> qKey;											// Key tail.
int             stdWidth		= 720;							// Standard width of the screen.
int             stdHeight		= 480;							// Standard height of the screen.
int             xMouseAxis		= 0;							// Current x coord of the mouse.
int             yMouseAxis		= 0;							// Current y coord of the mouse.
bool            mouseIsInScreen;								// Returns true if the mouse is inside of the screen.
bool            lButton[5];										// Left button of the mouse.
bool            rButton[5];										// Right button of the mouse.
bool            mButton[5];										// Middle button of the mouse.
char            szClassName[]	= "ZedStackWindow";				// Name for the window class.
/**  G L O B A L   V A R I A B L E S  **/

LRESULT CALLBACK windowProcedure (HWND, UINT, WPARAM, LPARAM);
COLORREF sdtColor = RGB (255, 255, 255);

VOID thread (PVOID pVoid) {
    Sleep (50);
    _main_ ();
}
void mayCallMain () {
    static bool started = false;

    if (!started) {
        _beginthread (thread, 0, NULL);
        started = true;
    }
}
void realFrame (int width, int height, int& retWidth, int& retHeight) {
    RECT frame = { 0, 0, width, height };
    AdjustWindowRect (&frame, WS_OVERLAPPEDWINDOW, FALSE);
    retWidth = frame.right - frame.left;
    retHeight = frame.bottom - frame.top;
}
void newMemDC (int width, int height) {
    if (hDeviceContext != NULL) {
		DeleteObject (hBitmap);
		DeleteDC (hDeviceContext);
	}
	HDC hDC = GetDC (hWindow);
	hDeviceContext = CreateCompatibleDC (hDC);
	hBitmap = CreateCompatibleBitmap (hDC, width, height);
	SelectObject (hDeviceContext, hBitmap);
	SetBkMode (hDeviceContext, TRANSPARENT);
}
LRESULT CALLBACK windowProcedure (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
        	case WM_SIZE: {
        		RECT rect;
                // TODO: Shuld i use "hWindow" instead?
        		GetClientRect (hWnd, &rect); // HACK: hWnd is defined in 66, but also in 18 (old code)
        		int width = rect.right - rect.left;
        		int height = rect.bottom - rect.top;

        		if (width == 0 && height == 0) break;

        		if (hDeviceContext == NULL || width != stdWidth || height != stdHeight) {
        			newMemDC (width, height);
        			mayCallMain ();
        		}
        		break;
        	}
        	case WM_SIZING: {
        		RECT* rect = (RECT*)lParam;

        		int width, height;
        		realFrame (stdWidth, stdHeight, width, height);

        		switch (wParam) {
            		case WMSZ_BOTTOM:		{ rect->bottom = rect->top + height; break; }
            		case WMSZ_TOP:			{ rect->top = rect->bottom - height; break; }
            		case WMSZ_RIGHT:		{ rect->right = rect->left + width;  break; }
            		case WMSZ_LEFT:			{ rect->left = rect->right - width;  break; }
            		case WMSZ_TOPLEFT:		{ rect->top = rect->bottom - height; rect->left = rect->right - width; break; }
            		case WMSZ_TOPRIGHT:		{ rect->top = rect->bottom - height; rect->left = rect->right + width; break; }
            		case WMSZ_BOTTOMLEFT:	{ rect->top = rect->bottom + height; rect->left = rect->right - width; break; }
            		case WMSZ_BOTTOMRIGHT:	{ rect->top = rect->bottom + height; rect->left = rect->right + width; break; }
        		}
        	}
        	case WM_PAINT: {
        		PAINTSTRUCT paintStruct;
        		HDC hDC = BeginPaint (hWnd, &paintStruct);
        		SelectObject (hDeviceContext, hBitmap);

        		if (hBitmap != NULL) BitBlt (hDC, 0, 0, stdWidth, stdHeight, hDeviceContext, 0, 0, SRCCOPY);
        		EndPaint (hWnd, &paintStruct);
        		break;
        	}
        	case WM_KEYDOWN: {
        		bool keyValue = false;

        		//! A - Z:
        		keyValue |= (wParam >= 65 && wParam <= 90);

        		//! Escape:
        		keyValue |= (wParam == VK_ESCAPE);

        		//! Space bar:
        		keyValue |= (wParam == VK_SPACE);

        		//! Return:
        		keyValue |= (wParam == VK_RETURN);

        		//! Arrows:
        		keyValue |= (wParam == VK_LEFT || wParam == VK_RIGHT || wParam == VK_UP || wParam == VK_DOWN);

        		//! F1 - F10:
        		for (unsigned int i = 0; i < 10; i++) keyValue |= (wParam == (VK_F1 + i));

        		//! 0 - 9:
        		keyValue |= (wParam >= 48 && wParam <= 57);

        		//! NP-0 - NP-9:
        		keyValue |= (wParam >= 96 && wParam <= 105);

        		if (keyValue) _key.push (wParam);
        		break;
        	}
        	case WM_MOUSEMOVE: {
        		TRACKMOUSEEVENT mouseEvent;
        		mouseEvent.cbSize = sizeof (TRACKMOUSEEVENT);
        		mouseEvent.hwndTrack = hWnd;
        		mouseEvent.dwFlags = TME_LEAVE; // TODO: do some research about "TME_HOVER"
        		mouseEvent.dwHoverTime = HOVER_DEFAULT;
        		TrackMouseEvent (&mouseEvent);

        		MOUSE_INSIDE = true;

        		xMouseAxis = GET_X_LPARAM (lParam);
        		yMouseAxis = GET_Y_LPARAM (lParam);

        		LBUTTON[UP]		=  !(wParam & MK_LBUTTON);
        		LBUTTON[DOWN]	=    wParam & MK_LBUTTON;
        		RBUTTON[UP]		=  !(wParam & MK_RBUTTON);
        		RBUTTON[DOWN]	= !!(wParam & MK_RBUTTON);
        		MBUTTON[UP]		=  !(wParam & MK_MBUTTON);
        		MBUTTON[DOWN]	= !!(wParam & MK_MBUTTON);
        		break;
        	}
        	case WM_MOUSELEAVE: {
        		MOUSE_INSIDE = false;
        		break;
        	}
        	case WM_MBUTTONUP: {
        		MBUTTON[UP] = true;
        		if (MBUTTON[SNGCK_1]) MBUTTON[SNGCK_2] = true;

        		MBUTTON[DOWN] = false;
        		MBUTTON[DBLCK] = false;
        		break;
        	}
        	case WM_MBUTTONDOWN: {
        		MBUTTON[DOWN] = true;
        		MBUTTON[SNGCK_1] = true;

        		MBUTTON[UP] = false;
        		break;
        	}
        	case WM_MBUTTONDBLCLK: {
        		MBUTTON[DBLCK] = true;

        		MBUTTON[SNGCK_1] = false;
        		MBUTTON[SNGCK_2] = false;
        		break;
        	}
        	case WM_LBUTTONUP: {
        		LBUTTON[UP] = true;
        		if (LBUTTON[SNGCK_1]) LBUTTON[SNGCK_2] = true;

        		LBUTTON[DOWN] = false;
        		LBUTTON[DBLCK] = false;
        		break;
        	}
        	case WM_LBUTTONDOWN: {
        		LBUTTON[DOWN] = true;
        		LBUTTON[SNGCK_1] = true;

        		LBUTTON[UP] = false;
        		break;
        	}
        	case WM_LBUTTONDBLCLK: {
        		LBUTTON[DBLCK] = true;

        		LBUTTON[SNGCK_1] = false;
        		LBUTTON[SNGCK_2] = false;
        		break;
        	}
        	case WM_RBUTTONUP: {
        		RBUTTON[UP] = true;
        		if (RBUTTON[SNGCK_1]) RBUTTON[SNGCK_2] = true;

        		RBUTTON[DOWN] = false;
        		RBUTTON[DBLCK] = false;
        		break;
        	}
        	case WM_RBUTTONDOWN: {
        		RBUTTON[DOWN] = true;
        		RBUTTON[SNGCK_1] = true;

        		RBUTTON[UP] = false;
        		break;
        	}
        	case WM_RBUTTONDBLCLK: {
        		MBUTTON[DBLCK] = true;

        		MBUTTON[SNGCK_1] = false;
        		MBUTTON[SNGCK_2] = false;
        		break;
        	}
        	case WM_DESTROY: {
        		DeleteObject (hBitmap);
        		DeleteDC (hDeviceContext);
        		PostQuitMessage (0);
        		break;
        	}
        	default: {
        		return DefWindowProc (hWnd, message, wParam, lParam);
        	}
    	}
	return 0;
}
int WINAPI WinMain (
    HINSTANCE hThisInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpszArgument,
    int nFunsterStil
) {
	static WNDCLASSEX wincl;

	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = windowProcedure;
	wincl.style = CS_DBLCLKS;
	wincl.cbSize = sizeof (WNDCLASSEX);
	wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	//wincl.hIcon = LoadIcon (hThisInstance, MAKEINTRESOURCE(IDI_ICON1));
	// TODO: Create new logos, menus and toolbars for the application if necessary.
	wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
	//wincl.hIconSm = LoadIcon (hThisInstance, MAKEINTRESOURCE(IDI_SMALL));
	//wincl.hIcon = LoadIcon(hThisInstance, MAKEINTRESOURCE(IDI_ICON1));
	// TODO: Create new logos, menus and toolbars for the application if necessary.
	wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
	//wincl.hIconSm = LoadIcon(hThisInstance, MAKEINTRESOURCE(IDI_SMALL));
	wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	wincl.hbrBackground = (HBRUSH)GetStockObject (BLACK_BRUSH);

	if (!RegisterClassEx (&wincl)) return 0;

	int width, height;
	realFrame (stdWidth, stdHeight, width, height);
	hWnd = CreateWindowEx (
		0,					//! Basic window style.
		szClassName,		//! Name of the class.
		title,				//! Title.
		WS_OVERLAPPEDWINDOW,//! Default window.
		CW_USEDEFAULT,		//! Windows decides the position -
		CW_USEDEFAULT,		//! - where the window ends up on the screen.
		width,				//! Window's width.
		height,				//! Window's height.
		HWND_DESKTOP,		//! The window is a child-window to desktop.
		NULL,				//! No menu.
		hThisInstance,		//! Program Instance handler.
		NULL);				//! No Window Creation data.
	hBitmap = NULL;
	ShowWindow (hWnd, nFunsterStil);
	MSG	messages;

	while (GetMessage (&messages, NULL, 0, 0)) {
		TranslateMessage (&messages);
		DispatchMessage (&messages);
	}
	return messages.wParam;
}

namespace ZedStackLibrary {
	SCREEN::SCREEN () {
        this.WIDTH = stdWidth;
        this.HEIGHT = stdHeight;
    }
} /* ZedStackLibrary */


#endif /* end of include guard: ZedStackLibrary */
