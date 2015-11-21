#ifndef ZedStackLibrary
#define ZedStackLibrary

// Needed libraryes:
#include <iostream>
#include <windows.h>


#ifndef _main_
#define _main_ main
#endif

int _main_ ();

namespace ZedStackLibrary {
	class SCREEN {
	private:
		int WIDTH;
		int HEIGHT;

		void rewriteStandards (int& oldWidth, int& oldHeight, int newWidth, int newHeight);
	public:
		SCREEN ();
		SCREEN (int width, int height);
		virtual ~SCREEN ();
		 // HACK: Make it possible for "center" or "upper-left", "upper-right", etc

		void getWidthAndHeight (int& retWidth, int& retHeight);
		void resize (int newHeight, int newHeight);
		void render ();
		void clear ();
		void close ();

		int getWidth ();
		int getHeight ();
	};
	class MOUSE {
	private:
		int xAxis;
		int yAxis;
	public:
		MOUSE ();
		MOUSE (int& xAxis, int& yAxis);
		MOUSE (bool& isInScreen);
		MOUSE ()
		virtual ~MOUSE ();

	};
} /* ZedStackLibrary */

#endif /* end of include guard: ZedStackLibrary */
