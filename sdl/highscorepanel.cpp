/** \file
 * File for the highscore panel.
 *
 * @author Nathan Samson
*/

#include <sstream>
#include <iostream>
#include <fstream>

#include "zabbr/resources/resourcemanager.h"

#include "highscorepanel.h"

namespace SISDL {
	/**
	 * Public constructor.
	 *
	 * @param window The SDLWIndow.
	 * @param score The score of the user
	*/
	HighscorePanel::HighscorePanel(Zabbr::SDLWindow* window, int score): Zabbr::VSDLPanel(window),
		     fHighscores(HighscorePanel::getHighscoreFile(), 50), fScore(score),
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
				blitScoreEntry(highscoreListSurface, (*it).first, (*it).second.first, (*it).second.second, false, y);
			}
			Zabbr::ResourceManager::manager().free(fFont);
		}
	}

	/**
	 * destructor.
	*/
	HighscorePanel::~HighscorePanel() {
		Zabbr::ResourceManager::manager().free(fTitleString);
		SDL_FreeSurface(highscoreListSurface);
	}

	/**
	 * Draw the controller.
	*/
	void HighscorePanel::draw() {
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
	void HighscorePanel::keyRelease(SDL_KeyboardEvent evnt) {
		if (fEnterHighscore) {
			fNameInputWidget->keyRelease(evnt);
			if (evnt.keysym.sym == SDLK_ESCAPE || evnt.keysym.sym == SDLK_RETURN) {
				fEnterHighscore = false;
				SI::Highscores::UpdatedHighscoreList hiList = fHighscores.setHighscore(fNameInputWidget->getValue(), fScore, 3, 8);
				delete fNameInputWidget;
				fHighscores.save(HighscorePanel::getHighscoreFile());
			
				highscoreListSurface = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, fWindow->getXResolution() - 240, fWindow->getYResolution() - 100, 32, 0, 0, 0, 0);

				int y = 0;
				for(SI::Highscores::UpdatedHighscoreList::iterator it = hiList.begin(); it != hiList.end(); it++) {
					blitScoreEntry(highscoreListSurface, (*it).first, (*it).second.getName(), (*it).second.getScore(), (*it).second.isUpdated(), y);
				}
				Zabbr::ResourceManager::manager().free(fFont);
			}
		} else {
			if (evnt.keysym.sym == SDLK_ESCAPE) {
				openParentPanel();
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
	void HighscorePanel::blitScoreEntry(SDL_Surface* surface,
	                                         int position,
	                                         std::string name,
	                                         int score, bool updated,
	                                         int& y) {
		SDL_Color color;
		if (!updated) {
			color.r = 255;
			color.g = 255;
			color.b = 255;
		} else {
			color.r = 0;
			color.g = 255;
			color.b = 0;
		}
			
		std::string entryString;
		std::stringstream ss;
		ss << position;
		ss >> entryString;
		entryString += ") " + name;
	
		Zabbr::StringFontResource* entryStringRes;
		entryStringRes = Zabbr::ResourceManager::manager().string(entryString, fFont, color);
		SDL_Rect dst;
		dst.x = 0;
		dst.y = y;
		SDL_BlitSurface(entryStringRes->getSurface(), 0, surface, &dst);
		Zabbr::ResourceManager::manager().free(entryStringRes);
	
		ss.clear();
		
		ss << score;
		ss >> entryString;
	
		entryStringRes = Zabbr::ResourceManager::manager().string(entryString, fFont, color);
		dst.x = surface->w - entryStringRes->getWidth();
		dst.y = y;
		SDL_BlitSurface(entryStringRes->getSurface(), 0, surface, &dst);
		y += entryStringRes->getHeight();
		Zabbr::ResourceManager::manager().free(entryStringRes);
	}
	
	/**
	 * Get the location of the higscore file.
	 * If the file does not exist write a default highscore file from data/ directory to the file.
	 *
	 * @return the location of the higscore file.
	*/
	std::string HighscorePanel::getHighscoreFile() {
		char* pFilePath = getenv("XDG_DATA_DIR");
		std::string fileName = "GPSI.high";
		std::string filePath;
		if (pFilePath == 0) {
			pFilePath = getenv("HOME");
			if (pFilePath == 0) {
				pFilePath = getenv("USERPROFILE");
				if (pFilePath == 0) {
					fileName = ".GPSI.high";
					filePath = "."; // Current Working directory...
				} else {
					filePath = pFilePath;
					filePath += "/.local/share";
				}
			} else {
				filePath = pFilePath;
				filePath += "/.local/share";
			}
		} else {
			filePath = pFilePath;
		}
		
		FILE* pFile = fopen((filePath+"/"+fileName).c_str(), "r");
		if (pFile == 0) {
			// Copy data file to filePath
			
			std::ifstream is;
			std::ofstream os;
			std::filebuf* fb;
			
			is.open((Zabbr::ResourceManager::fgDataPath+"/default.high").c_str(), std::ios_base::in);
			fb = os.rdbuf();
			fb->open ((filePath+"/"+fileName).c_str(), std::ios_base::out);
			is >> fb;
			
			fb->close();
			is.close();
		} else {
			fclose(pFile);
		}
		return filePath+"/"+fileName;
	}
}
