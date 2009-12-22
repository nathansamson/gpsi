#include "sdlship.h"
#include "zabbr/resources/resourcemanager.h"

namespace SISDL {
	class SDLUserShip: public SDLShip {
	public:
		SDLUserShip(SI::VShipDriver*, SI::Vector2, int,
	                 SI::EntityGroup*, SI::ShipType,
	                 SI::IGameEntityFactory*, SI::Weaponery*,
	                 Zabbr::SDLWindow*);
		virtual ~SDLUserShip();
	
		virtual void visualize();
	private:
		Zabbr::FontResource* fFont;
		Zabbr::StringFontResource* fHealthText;
	};
}
