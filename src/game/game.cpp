#include "game.h"

namespace SI {
	/**
	 * Constructor.
	 *
	 * @param userShipDriver The VShipDriver for the user ship.
	 * @param entityFactory The Entity factory for this game.
	*/
	Game::Game(VShipDriver* userShipDriver, IGameEntityFactory* entityFactory) : fEntityFactory(entityFactory) {
		Ship* user = entityFactory->createShip(userShipDriver);
		fEntities.push_back(user);
	}
	
	Game::~Game() {
		for(std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end(); it++) {
			delete (*it);
		}
		delete fEntityFactory;
	}
	
	/**
	 * Update the game state. All entities will be updated. Afterwards all entities will be visualized.
	 *
	 * @param ticks The number of ticks passed since last update.
	*/
	void Game::update(int ticks) {
		for(std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end(); it++) {
			(*it)->update(ticks);
		}
		
		for(std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end(); it++) {
			(*it)->visualize();
		}
	}
}
