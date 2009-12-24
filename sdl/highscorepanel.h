#ifndef INC_HIGHSCORE_PANEL
#define INC_HIGHSCORE_PANEL

#include "zabbr/panels/sdlpanel.h"
#include "zabbr/widgets/textinput.h"

#include "src/misc/highscores.h"

namespace SISDL {
	/**
	 * A panel to draw highscores and insert a new highscore
	*/
	class HighscorePanel: public Zabbr::VSDLPanel {
	public:
		HighscorePanel(Zabbr::SDLWindow*, int);		
		virtual ~HighscorePanel();

		virtual void draw();
		virtual void keyRelease(SDL_KeyboardEvent evnt);
	private:
		void blitScoreEntry(SDL_Surface* surface, int position,
	                        SI::Highscores::ScoreEntry entry, int& y);
	
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
		
		/**
		 * The font.
		*/
		Zabbr::FontResource* fFont;
		
		/**
		 * The title string.
		*/
		Zabbr::StringFontResource* fTitleString;

		/**
		 * The higschore list surface.
		*/
		SDL_Surface* highscoreListSurface;
	};
}

#endif // INC_HIGHSCORE_PANEL
