#include "zabbr/controller/sdlcontroller.h"
#include "zabbr/widgets/textinput.h"

#include "src/misc/highscores.h"

namespace SISDL {
	/**
	 * A controller to draw highscores and insert a new highscore
	*/
	class HighscoreController: public Zabbr::VSDLController {
	public:
		HighscoreController(Zabbr::SDLWindow*, int);		
		virtual ~HighscoreController();

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
