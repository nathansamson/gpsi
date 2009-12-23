#include <sstream>
#include "sdlusership.h"

namespace SISDL {
	/**
	 * Constructor.
	 *
	 * @param driver The driver.
	 * @param v The position
	 * @param dir The direction
	 * @param group The group
	 * @param t The ship type
	 * @param fac The entity factory.
	 * @param weaponery The weaponery
	 * @param w The SDLWindow
	*/
	SDLUserShip::SDLUserShip(SI::VShipDriver* driver, SI::Vector2 v, int dir,
	                 SI::EntityGroup* group,
	                 SI::ShipType t, SI::IGameEntityFactory* fac,
	                 SI::Weaponery* weaponery, Zabbr::SDLWindow* w): SDLShip(driver, v, dir, group, t, fac, weaponery, w) {
		fFont = Zabbr::ResourceManager::manager().font("DejaVuSans-Bold.ttf", 16);
	}
	
	SDLUserShip::~SDLUserShip() {
		Zabbr::ResourceManager::manager().free(fFont);
	}

	/**
	 * Draws the ship on the screen.
	*/
	void SDLUserShip::visualize() {
		SDLShip::visualize();
		
		
		std::stringstream ss;
		ss << static_cast<int>(getHealth()*100);
		
		std::string healthString;
		ss >> healthString;
		healthString = "Health: " + healthString + "/100";
		
		SDL_Color textColor = {0, 255, 0};
		if (getHealth() < 0.35) {
			textColor.r = 255;
			textColor.g = 0;
			textColor.b = 0;
		} else if (getHealth() < 0.65) {
			textColor.r = 255;
			textColor.g = 255;
			textColor.b = 0;
		}
		
		fHealthText = Zabbr::ResourceManager::manager().string(healthString, fFont, textColor);
		fWindow->drawSurface(fHealthText, 10, fWindow->getYResolution() - 10 - fHealthText->getHeight());
		Zabbr::ResourceManager::manager().free(fHealthText);
	}
}
