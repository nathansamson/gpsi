#include "tclap/CmdLine.h"

#include "siwindow.h"

int main(int argc, char* argv[]) {
	TCLAP::CmdLine cmd("Space-Invaders", ' ', "0.1");
	TCLAP::SwitchArg game("g", "game", "Start a new game, instead of fist opening the menu.");
	TCLAP::SwitchArg demo("d", "demo", "Run the game in demo mode (no user input for game).");
	try {		
		cmd.add(game);
		cmd.add(demo);
		cmd.parse(argc, argv);
	} catch (...) {
		return 1;
	}
	
	SISDL::SIWindow* win = new SISDL::SIWindow();
	if (! demo.getValue()) {
		win->run(game.getValue());
	} else {
		win->rundemo();
	}

	delete win;
	return 0;
}
