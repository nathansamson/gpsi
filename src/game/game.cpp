#include "game.h"

namespace SI {
	/**
	 * Constructor.
	 *
	 * @param userShipDriver The VShipDriver for the user ship.
	 * @param entityFactory The Entity factory for this game.
	*/
	Game::Game(VShipDriver* userShipDriver, IGameEntityFactory* entityFactory, IEnemyDriverFactory* enemyDriverFactory) 
	     : fEntityFactory(entityFactory), fEnemyDriverFactory(enemyDriverFactory) {
		Ship* user = entityFactory->createShip(userShipDriver, Vector2(0, -2.0));
		fEntities.push_back(user);
		
		for (int i = 0; i < 5; i++) {
			fEntities.push_back(entityFactory->createShip(enemyDriverFactory->createEnemyDriver(), Vector2(-3.0+i*(7.0/5), 2.0)));
		}
	}
	
	Game::~Game() {
		for(std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end(); it++) {
			delete (*it);
		}
		delete fEntityFactory;
		delete fEnemyDriverFactory;
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
