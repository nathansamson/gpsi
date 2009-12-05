#include "src/game/gameentityfactory.h"
#include "zabbr/sdlwindow.h"

namespace SISDL {
	/**
	 * The SDLEntity factory.
	*/
	class SDLEntityFactory: public SI::IGameEntityFactory {
	public:
		SDLEntityFactory(Zabbr::SDLWindow*);
		SI::Ship* createShip(SI::VShipDriver*, SI::Vector2, SI::ShipType);
		SI::Bullet* createBullet(SI::Vector2, SI::BulletType);
	private:
		/**
		 * The window to draw the widgets on.
		*/
		Zabbr::SDLWindow* fWindow;
	};
}
