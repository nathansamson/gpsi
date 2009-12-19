#include "sdlentityfactory.h"
#include "sdlship.h"
#include "sdlbullet.h"
#include "sdlclusterbomb.h"

namespace SISDL {
	/**
	 * Public constructor
	 *
	 * @param w The window
	*/
	SDLEntityFactory::SDLEntityFactory(Zabbr::SDLWindow* w): fWindow(w) {
	}

	/**
	 * Creates a ship.
	 *
	 * @param driver The driver for the ship.
	 * @param d The initial direction of the ship.
	 * @param g The group of the entity.
	 * @param v The initial position.
	 * @param t The type of the ship.
	*/
	SI::Ship* SDLEntityFactory::createShip(SI::VShipDriver* driver, SI::Vector2 v, int d, SI::EntityGroup* g, SI::Weaponery* w, SI::ShipType t) {
		return new SDLShip(driver, v, d, g, t, this, w, fWindow);
	}
	
	/**
	 * Creates a bullet
	 *
	 * @param pos The initial position of the bullet.
	 * @param dir The initial direction of the bullet.
	 * @param t Bullet information
	*/
	SI::Bullet* SDLEntityFactory::createBullet(SI::Vector2 pos, int dir, SI::EntityGroup* g, SI::BulletType* t) {
		return new SDLBullet(pos, dir, g, t, this, fWindow);
	}
	
	/**
	 * Creates a cluster bomb
	 *
	 * @param pos The initial position of the cluster bomb.
	 * @param dir The initial direction of the cluster bomb.
	 * @param t Cluster bomb information
	*/
	SI::ClusterBomb* SDLEntityFactory::createClusterBomb(SI::Vector2 pos, int dir,
	                  SI::EntityGroup* g, SI::ClusterBombType* t) {
		return new SDLClusterBomb(pos, dir, g, t, this, fWindow);
	}
}
