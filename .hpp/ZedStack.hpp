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
		
	};
} /* ZedStackLibrary */

#endif /* end of include guard: ZedStackLibrary */
