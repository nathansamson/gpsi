/** \file
 * File for the highscore panel.
 *
 * @author Nathan Samson
*/

#include <sstream>
#include <iostream>
#include <fstream>

#include "zabbr/widgets/label.h"
#include "zabbr/widgets/hbox.h"
#include "zabbr/widgets/vbox.h"
#include "zabbr/resources/resourcemanager.h"
#include "highscorepanel.h"

namespace SISDL {
	/**
	 * Public constructor.
	 *
	 * @param window The SDLWIndow.
	 * @param score The score of the user
	*/
	HighscorePanel::HighscorePanel(Zabbr::SDLWindow* window, int score):
	         Zabbr::WidgetPanel(window, new Zabbr::VBox(window, false, 10)),
		     fHighscores(HighscorePanel::getHighscoreFile(), 50), fScore(score),
		     fEnterHighscore(fHighscores.isHighscore(score)) {	
		
		if (fEnterHighscore) {
			fNameInputWidget = new Zabbr::TextInputWidget(fWindow, "Nathan Samson");
			dynamic_cast<Zabbr::VBox*>(fTopLevel)->appendWidget(fNameInputWidget);
			dynamic_cast<Zabbr::VBox*>(fTopLevel)->setYAlign(Zabbr::YALIGN_CENTER);
		} else {
			SDL_Color white = {255, 255, 255};
			Zabbr::Label* titleLabel = new Zabbr::Label(fWindow, "Highscores", white, Zabbr::FONTSIZE_MEDIUM);
			dynamic_cast<Zabbr::VBox*>(fTopLevel)->appendWidget(titleLabel);
			Zabbr::HBox* scoreHBox = new Zabbr::HBox(window, false, 5);
			dynamic_cast<Zabbr::VBox*>(fTopLevel)->appendWidget(scoreHBox);
			
			Zabbr::VBox* posBox = new Zabbr::VBox(fWindow, false, 5, Zabbr::XALIGN_RIGHT, Zabbr::YALIGN_CENTER);
			scoreHBox->appendWidget(posBox);
			Zabbr::VBox* nameBox = new Zabbr::VBox(fWindow, false, 5, Zabbr::XALIGN_LEFT, Zabbr::YALIGN_CENTER);
			scoreHBox->appendWidget(nameBox);
			Zabbr::VBox* scoreBox = new Zabbr::VBox(fWindow, false, 5, Zabbr::XALIGN_LEFT, Zabbr::YALIGN_CENTER);
			scoreHBox->appendWidget(scoreBox);
			
			SI::Highscores::HighscoreList hiList = fHighscores.getBestHighscores(15);
			for(SI::Highscores::HighscoreList::iterator it = hiList.begin(); it != hiList.end(); it++) {
				addScoreEntryToTable(posBox, nameBox, scoreBox, (*it).first,
				                     (*it).second.first, (*it).second.second,
				                     false);
			}
			nameBox->setWidth(400 - scoreBox->getWidth() - posBox->getWidth());
		}
	}

	/**
	 * destructor.
	*/
	HighscorePanel::~HighscorePanel() {
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
				fNameInputWidget = 0;
				dynamic_cast<Zabbr::VBox*>(fTopLevel)->clear();
				dynamic_cast<Zabbr::VBox*>(fTopLevel)->setYAlign(Zabbr::YALIGN_TOP);
				fHighscores.save(HighscorePanel::getHighscoreFile());
			
				SDL_Color white = {255, 255, 255};
				Zabbr::Label* titleLabel = new Zabbr::Label(fWindow, "Highscores", white, Zabbr::FONTSIZE_MEDIUM);
				dynamic_cast<Zabbr::VBox*>(fTopLevel)->appendWidget(titleLabel);
				Zabbr::HBox* scoreHBox = new Zabbr::HBox(fWindow, false, 5);
				dynamic_cast<Zabbr::VBox*>(fTopLevel)->appendWidget(scoreHBox);
			
				Zabbr::VBox* posBox = new Zabbr::VBox(fWindow, false, 5, Zabbr::XALIGN_RIGHT, Zabbr::YALIGN_CENTER);
				scoreHBox->appendWidget(posBox);
				Zabbr::VBox* nameBox = new Zabbr::VBox(fWindow, false, 5, Zabbr::XALIGN_LEFT, Zabbr::YALIGN_CENTER);
				scoreHBox->appendWidget(nameBox);
				Zabbr::VBox* scoreBox = new Zabbr::VBox(fWindow, false, 5, Zabbr::XALIGN_LEFT, Zabbr::YALIGN_CENTER);
				scoreHBox->appendWidget(scoreBox);

				for(SI::Highscores::UpdatedHighscoreList::iterator it = hiList.begin(); it != hiList.end(); it++) {
					addScoreEntryToTable(posBox, nameBox, scoreBox, (*it).first,
						                 (*it).second.getName(), (*it).second.getScore(),
						                 (*it).second.isUpdated());
				}
				nameBox->setWidth(400 - scoreBox->getWidth() - posBox->getWidth());
			}
		} else {
			if (evnt.keysym.sym == SDLK_ESCAPE) {
				openParentPanel();
			}
		}
	}
	
	/**
	 * Helper function add an entry to the table.
	 *
	 * @param posBox The VBox with all positions
	 * @param nameBox The VBox with all names
	 * @param scoreBox The VBx with all scores.
	 * @param position The position in the highscore list.
	 * @param name The name of the entry
	 * @param updated If the entry is updated (and should have another color)
	*/
	void HighscorePanel::addScoreEntryToTable(Zabbr::VBox* posBox,
	                                          Zabbr::VBox* nameBox,
	                                          Zabbr::VBox* scoreBox,
	                                          int position, std::string name,
	                                          int score, bool updated) {
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
		entryString += ")";

		Zabbr::Label* posLabel = new Zabbr::Label(fWindow, entryString, color, Zabbr::FONTSIZE_SMALL);
		posBox->appendWidget(posLabel);
		
		Zabbr::Label* nameLabel = new Zabbr::Label(fWindow, name, color, Zabbr::FONTSIZE_SMALL);
		nameBox->appendWidget(nameLabel);
		
		ss.clear();
		ss << score;
		ss >> entryString;
		
		Zabbr::Label* scoreLabel = new Zabbr::Label(fWindow, entryString, color, Zabbr::FONTSIZE_SMALL);
		scoreBox->appendWidget(scoreLabel);
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
