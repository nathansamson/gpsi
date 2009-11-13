#include "siwindow.h"

int main() {
	sisdl::SIWindow* win = new sisdl::SIWindow();
	win->run();

	delete win;
}
