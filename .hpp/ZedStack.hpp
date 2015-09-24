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
		int privWidth;
		int privHeight;

		void rewriteStandards (int& oldWidth, int& oldHeight, int newWidth, int newHeight);
	public:
		SCREEN ();
		SCREEN (int width, int height);
		virtual ~SCREEN ();
		 // TODO: Make it possible for "center" or "upper-left", "upper-right", etc

		void getWidthAndHeight (int& retWidth, int& retHeight);
		void resize (int newHeight, int newHeight);
		void render ();
		void clear ();
		void close ();

		int getWidth ();
		int getHeight ();
	};
} /* ZedStackLibrary */

#endif /* end of include guard: ZedStackLibrary */
