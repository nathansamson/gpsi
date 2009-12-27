#ifndef INC_SDLUSERSHIP_H
#define INC_SDLUSERSHIP_H

#include "sdlship.h"
#include "zabbr/widgets/label.h"

/** \file
 * File for the SDL user ship.
 *
 * @author Nathan Samson
*/

namespace SISDL {
	/**
	 * A SDL User ship. (it draws also the health)
	*/
	class SDLUserShip: public SDLShip {
	public:
		SDLUserShip(SI::VShipDriver*, SI::Vector2, int,
	                 SI::EntityGroup*, SI::ShipType,
	                 SI::IGameEntityFactory*, SI::Weaponery*,
	                 Zabbr::SDLWindow*);
		virtual ~SDLUserShip();
	
		virtual void visualize();
	private:
		Zabbr::Label* fLabelWidget;
	};
}

#endif // INC_SDLUSERSHIP_H
