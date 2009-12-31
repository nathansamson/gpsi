#ifndef INC_HIGHSCORE_PANEL
#define INC_HIGHSCORE_PANEL

/** \file
 * File for the highscore panel.
 *
 * @author Nathan Samson
*/

#include "zabbr/panels/widgetpanel.h"
#include "zabbr/widgets/textinput.h"
#include "zabbr/widgets/vbox.h"

#include "src/misc/highscores.h"

namespace SISDL {
	/**
	 * A panel to draw highscores and insert a new highscore
	*/
	class HighscorePanel: public Zabbr::WidgetPanel {
	public:
		HighscorePanel(Zabbr::SDLWindow*, int);		
		virtual ~HighscorePanel();

		//virtual void draw();
		virtual void keyPress(SDL_KeyboardEvent);
		virtual void keyRelease(SDL_KeyboardEvent);
	private:
		static std::string getHighscoreFile();
		void addScoreEntryToTable(Zabbr::VBox*, Zabbr::VBox*, Zabbr::VBox*,
		                          int, std::string, int, bool);
	
		/**
		 * The highscore list 
		*/
		SI::Highscores fHighscores;
		
		/**
		 * The new score.
		*/
		int fScore;
		
		/**
		 * If we are in the enter higscore phase
		*/
		bool fEnterHighscore;
		
		/**
		 * The text input field.
		*/
		Zabbr::TextInputWidget* fNameInputWidget;
	};
}

#endif // INC_HIGHSCORE_PANEL
