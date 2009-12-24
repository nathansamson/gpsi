#include <sstream>

#include "highscorecontroller.h"

namespace SISDL {
	/**
	 * Public constructor.
	 *
	 * @param window The SDLWIndow.
	 * @param score The score of the user
	*/
	HighscoreController::HighscoreController(Zabbr::SDLWindow* window, int score): Zabbr::VSDLController(window),
		     fHighscores(".gpsi.high", 50), fScore(score),
		     fEnterHighscore(fHighscores.isHighscore(score)) {	
		fFont = Zabbr::ResourceManager::manager().font("DejaVuSans-Bold.ttf", 18);
		
		Zabbr::FontResource* titleFont = Zabbr::ResourceManager::manager().font("DejaVuSans-Bold.ttf", 32);
		SDL_Color white = {255, 255, 255};
		fTitleString = Zabbr::ResourceManager::manager().string("Highscores", titleFont, white);
		Zabbr::ResourceManager::manager().free(titleFont);
		
		if (fEnterHighscore) {
			fNameInputWidget = new Zabbr::TextInputWidget(fWindow, "Nathan Samson");
		} else {
			SI::Highscores::HighscoreList hiList = fHighscores.getBestHighscores(15);
			highscoreListSurface = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, fWindow->getXResolution() - 240, fWindow->getYResolution() - 100, 32, 0, 0, 0, 0);

			int y = 0;
			for(SI::Highscores::HighscoreList::iterator it = hiList.begin(); it != hiList.end(); it++) {
				blitScoreEntry(highscoreListSurface, (*it).first, (*it).second, y);
			}
			Zabbr::ResourceManager::manager().free(fFont);
		}
	}

	/**
	 * destructor.
	*/
	HighscoreController::~HighscoreController() {
		Zabbr::ResourceManager::manager().free(fTitleString);
		SDL_FreeSurface(highscoreListSurface);
	}

	/**
	 * Draw the controller.
	*/
	void HighscoreController::draw() {
		if (fEnterHighscore) {
			fNameInputWidget->draw(fWindow->getXResolution() / 2, fWindow->getYResolution() / 2 - fNameInputWidget->getHeight()/2);
		} else {
			fWindow->drawSurface(fTitleString, fWindow->getXResolution() / 2 - fTitleString->getWidth() / 2, 10);
			fWindow->drawSurface(highscoreListSurface, 120, 50);
		}
	}

	/**
	 * Method called by the window if a key is released.
	 *
	 * @param evnt The SDL_KeyboardEvent
	*/
	void HighscoreController::keyRelease(SDL_KeyboardEvent evnt) {
		if (fEnterHighscore) {
			fNameInputWidget->keyRelease(evnt);
			if (evnt.keysym.sym == SDLK_ESCAPE || evnt.keysym.sym == SDLK_RETURN) {
				fEnterHighscore = false;
				SI::Highscores::HighscoreList hiList = fHighscores.setHighscore(fNameInputWidget->getValue(), fScore, 3, 8);
				delete fNameInputWidget;
				fHighscores.save(".gpsi.high");
			
				highscoreListSurface = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, fWindow->getXResolution() - 240, fWindow->getYResolution() - 100, 32, 0, 0, 0, 0);

				int y = 0;
				for(SI::Highscores::HighscoreList::iterator it = hiList.begin(); it != hiList.end(); it++) {
					blitScoreEntry(highscoreListSurface, (*it).first, (*it).second, y);
				}
				Zabbr::ResourceManager::manager().free(fFont);
			}
		} else {
			if (evnt.keysym.sym == SDLK_ESCAPE) {
				openParentController();
			}
		}
	}
	
	/**
	 * Helper function to blit score entries on a surface.
	 *
	 * @param surface The surface to blit on.
	 * @param position The position in the highscore list.
	 * @param entry The entry
	 * @param y The y coordinate of the entry
	*/
	void HighscoreController::blitScoreEntry(SDL_Surface* surface,
	                                         int position,
	                                         SI::Highscores::ScoreEntry entry,
	                                         int& y) {
		SDL_Color white = {255, 255, 255};
		std::string entryString;
		std::stringstream ss;
		ss << position;
		ss >> entryString;
		entryString += ") " + entry.first;
	
		Zabbr::StringFontResource* entryStringRes;
		entryStringRes = Zabbr::ResourceManager::manager().string(entryString, fFont, white);
		SDL_Rect dst;
		dst.x = 0;
		dst.y = y;
		SDL_BlitSurface(entryStringRes->getSurface(), 0, surface, &dst);
		Zabbr::ResourceManager::manager().free(entryStringRes);
	
		ss.clear();
		ss << entry.second;
		ss >> entryString;
	
		entryStringRes = Zabbr::ResourceManager::manager().string(entryString, fFont, white);
		dst.x = surface->w - entryStringRes->getWidth();
		dst.y = y;
		SDL_BlitSurface(entryStringRes->getSurface(), 0, surface, &dst);
		y += entryStringRes->getHeight();
		Zabbr::ResourceManager::manager().free(entryStringRes);
	}
}
