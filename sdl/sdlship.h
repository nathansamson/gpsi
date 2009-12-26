#ifndef INC_SDLSHIP_H
#define INC_SDLSHIP_H

/** \file
 * File for the SDL ship.
 *
 * @author Nathan Samson
*/

#include "src/game/ship.h"
#include "zabbr/resources/imageresource.h"
#include "zabbr/sdlwindow.h"

namespace SISDL {
	/**
	 * A Ship visualized by SDL.
	*/
	class SDLShip: public SI::Ship {
	public:
		SDLShip(SI::VShipDriver*, SI::Vector2, int, SI::EntityGroup*,
		        SI::ShipType, SI::IGameEntityFactory*,
				SI::Weaponery*, Zabbr::SDLWindow*);
		virtual ~SDLShip();
		
		virtual std::vector<VGameEntity*> update(int);
		virtual void visualize();
		virtual bool isVisible();
	protected:
		/**
		 * The window.
		*/
		Zabbr::SDLWindow* fWindow;
	private:
		/**
		 * The image resource.
		*/
		Zabbr::ImageResource* fImage;
		
		void positionToWindowCoords(int&, int&);
		
		/**
		 * Number of ticks passed since dead.
		*/
		int ticksSinceDead;
	};
}

#endif // INC_SDLSHIP_H
