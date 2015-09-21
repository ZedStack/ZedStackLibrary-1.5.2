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


/**  G L O B A L   V A R I A B L E S  **/
HWND            hWindow;									// Main screen.
HBITMAP         hBitmap;									// Bitmap of the screen.
HDC             hDeviceContext	= NULL;						// Device context.
LPCSTR          lpcTitle		= "ZedStack Library Project";// Title of the window.
std::queue<int> qKey;										// Key tail.
int             stdWidth		= 720;						// Standard width of the screen.
int             stdHeight		= 480;						// Standard height of the screen.
int             xMouseAxis		= 0;						// Current x coord of the mouse.
int             yMouseAxis		= 0;						// Current y coord of the mouse.
bool            mouseIsInScreen;							// Returns true if the mouse is inside of the screen.
bool            lButton[5];									// Left button of the mouse.
bool            rButton[5];									// Right button of the mouse.
bool            mButton[5];									// Middle button of the mouse.
char            szClassName[]	= "ZedStackWindow";			// Name for the window class.
/**  G L O B A L   V A R I A B L E S  **/


#endif /* end of include guard: ZedStackLibrary */
