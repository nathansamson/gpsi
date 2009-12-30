#include <iostream>

#include "SDL.h"

#include "zabbr/widgets/vbox.h"
#include "zabbr/widgets/table.h"
#include "zabbr/widgets/label.h"
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
		
		Zabbr::Table* table = new Zabbr::Table(fWindow, 30, 10, 4, 2);
		table->setWidget(new Zabbr::Label(fWindow, "Resolution", white), 0, 0);
		table->setWidget(new Zabbr::Label(fWindow, "Placeholder", white), 0, 1);
		
		table->setWidget(new Zabbr::Label(fWindow, "Fullscreen*", white), 1, 0);
		fFullscreenCheckbox = new Zabbr::CheckBox(fWindow, false);
		table->setWidget(fFullscreenCheckbox, 1, 1);
		
		table->setWidget(new Zabbr::Label(fWindow, "Sound", white), 2, 0);
		fSoundCheckbox = new Zabbr::CheckBox(fWindow, false);
		table->setWidget(fSoundCheckbox, 2, 1);
		
		table->setWidget(new Zabbr::Label(fWindow, "Name", white), 3, 0);
		fNameInput = new Zabbr::TextInputWidget(fWindow, "Nathan Samson");
		fNameInput->setWidth(150);
		table->setWidget(fNameInput, 3, 1);
		
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
		std::cout << fNameInput->getValue() << std::endl;
		openParentPanel();
	}
}
