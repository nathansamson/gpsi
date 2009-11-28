#include "siwindow.h"

int main() {
	SISDL::SIWindow* win = new SISDL::SIWindow();
	win->run();

	delete win;
}
