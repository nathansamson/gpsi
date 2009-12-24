#include "tclap/CmdLine.h"

#include "siwindow.h"

int main(int argc, char* argv[]) {
	TCLAP::CmdLine cmd("Space-Invaders", ' ', "0.1");
	TCLAP::SwitchArg demo("g", "game", "Start a new game, instead of fist opening the menu.");
	try {		
		cmd.add(demo);
		cmd.parse(argc, argv);
	} catch (...) {
		return 1;
	}
	
	SISDL::SIWindow* win = new SISDL::SIWindow();
	win->run(demo.getValue());

	delete win;
	return 0;
}
