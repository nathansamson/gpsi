#ifndef INC_OPTIONSPANEL_H
#define INC_OPTIONSPANEL_H

#include "zabbr/panels/widgetpanel.h"
#include "zabbr/widgets/button.h"
#include "zabbr/widgets/textinput.h"

namespace SISDL {
	/**
	 * Panel that shows the options for the game.
	*/
	class OptionsPanel: public Zabbr::WidgetPanel {
	public:
		OptionsPanel(Zabbr::SDLWindow*);
		
	private:
		void onKeyRelease(Zabbr::VSDLPanel*, SDL_KeyboardEvent evnt);
		void onBackButtonClicked(Zabbr::Button*);
		void onQuitRequest();
		void saveAndClose();
		
		Zabbr::TextInputWidget* fNameInput;
	};
}

#endif // INC_OPTIONSPANEL_H
