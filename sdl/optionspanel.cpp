#include <iostream>

#include "SDL.h"

#include "zabbr/widgets/vbox.h"
#include "zabbr/widgets/table.h"
#include "zabbr/widgets/label.h"
#include "zabbr/misc/audiomanager.h"
#include "configurationmanager.h"
#include "optionspanel.h"

namespace SISDL {
	/**
	 * Public constructor.
	 *
	 * @param w The window
	*/
	OptionsPanel::OptionsPanel(Zabbr::SDLWindow* w):
	              WidgetPanel(w, new Zabbr::VBox(w, false, 10)) {
		
		SDL_Color white = {255, 255, 255};
		dynamic_cast<Zabbr::VBox*>(fTopLevel)->appendWidget(new Zabbr::Label(fWindow, "Options", white, Zabbr::FONTSIZE_BIG));
		
		Zabbr::Table* table = new Zabbr::Table(fWindow, 30, 10, 5, 2);
		table->setWidget(new Zabbr::Label(fWindow, "Resolution", white), 0, 0);
		fResolutionCombobox = new Zabbr::ComboBox<Zabbr::VideoMode>(fWindow);
		std::vector<Zabbr::VideoMode> resolutions = fWindow->getAvailableResolutions();
		for(std::vector<Zabbr::VideoMode>::iterator it = resolutions.begin(); it != resolutions.end(); it++) {
			fResolutionCombobox->addOption((*it));
		}
		fResolutionCombobox->setSelectedOption(fWindow->getVideoMode());
		table->setWidget(fResolutionCombobox, 0, 1);
		
		table->setWidget(new Zabbr::Label(fWindow, "Fullscreen*", white), 1, 0);
		fFullscreenCheckbox = new Zabbr::CheckBox(fWindow, ConfigurationManager::getOption("fullscreen", false));
		table->setWidget(fFullscreenCheckbox, 1, 1);
		
		table->setWidget(new Zabbr::Label(fWindow, "Music", white), 2, 0);
		fMusicCheckbox = new Zabbr::CheckBox(fWindow, ConfigurationManager::getOption("play-music", false));
		table->setWidget(fMusicCheckbox, 2, 1);
		
		table->setWidget(new Zabbr::Label(fWindow, "Sound", white), 3, 0);
		fSoundCheckbox = new Zabbr::CheckBox(fWindow, ConfigurationManager::getOption("play-sound", true));
		table->setWidget(fSoundCheckbox, 3, 1);
		
		table->setWidget(new Zabbr::Label(fWindow, "Name", white), 4, 0);
		fNameInput = new Zabbr::TextInputWidget(fWindow, ConfigurationManager::getOption<std::string>("name", "Nathan Samson"));
		fNameInput->setWidth(150);
		table->setWidget(fNameInput, 4, 1);
		
		dynamic_cast<Zabbr::VBox*>(fTopLevel)->appendWidget(table);
		
		Zabbr::Button* back = new Zabbr::Button(fWindow, "Back");
		back->connectOnClicked(new Zabbr::ClassCallback1<OptionsPanel, Zabbr::Button*>(this, &OptionsPanel::onBackButtonClicked));
		dynamic_cast<Zabbr::VBox*>(fTopLevel)->appendWidget(back);
		
		Zabbr::Label* restartLabel = new Zabbr::Label(fWindow, "* needs restart", white, Zabbr::FONTSIZE_SMALL);
		dynamic_cast<Zabbr::VBox*>(fTopLevel)->appendWidget(restartLabel);
		
		connectOnKeyRelease(new Zabbr::ClassCallback2<OptionsPanel, Zabbr::VSDLPanel*, SDL_KeyboardEvent>(this, &OptionsPanel::onKeyRelease));
		connectRequestQuit(new Zabbr::ClassCallback0<OptionsPanel>(this, &OptionsPanel::onQuitRequest));
	}
	
	/**
	 * Key release callback
	 *
	 * @param evnt The keyboard event.
	*/
	void OptionsPanel::onKeyRelease(Zabbr::VSDLPanel*, SDL_KeyboardEvent evnt) {
		if (evnt.keysym.sym == SDLK_ESCAPE) {
			saveAndClose();
		}
	}
	
	/**
	 * The back button clicked callback.
	*/
	void OptionsPanel::onBackButtonClicked(Zabbr::Button*) {
		saveAndClose();
	}
	
	/**
	 * Quit request callback.
	*/
	void OptionsPanel::onQuitRequest() {
		saveAndClose();
	}
	
	/**
	 * Save the settings and close the window.
	*/
	void OptionsPanel::saveAndClose() {
		ConfigurationManager::setOption<int>("xres", fResolutionCombobox->getSelectedOption().getX());
		ConfigurationManager::setOption<int>("yres", fResolutionCombobox->getSelectedOption().getY());
		fWindow->resize(fResolutionCombobox->getSelectedOption());
		ConfigurationManager::setOption("fullscreen", fFullscreenCheckbox->isEnabled());
		ConfigurationManager::setOption("play-music", fMusicCheckbox->isEnabled());
		ConfigurationManager::setOption("play-sound", fSoundCheckbox->isEnabled());
		
		if (ConfigurationManager::getOption("play-music", false)) {
			Zabbr::AudioManager::get().startMusic();
		} else {
			Zabbr::AudioManager::get().stopMusic();
		}
		
		if (!ConfigurationManager::getOption("play-sound", true)) {
			Zabbr::AudioManager::get().mute();
		} else {
			Zabbr::AudioManager::get().unmute();
		}
		ConfigurationManager::setOption<std::string>("name", fNameInput->getValue());
		openParentPanel();
	}
}
