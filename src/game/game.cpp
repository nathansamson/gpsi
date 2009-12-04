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
			fEntities.push_back(entityFactory->createShip(enemyDriverFactory->createEnemyDriver(), Vector2(-4.0+(i+1)*8.0/6, 2.5)));
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
		std::vector<VGameEntity*> newEnts;
		for(std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end(); it++) {
			std::vector<VGameEntity*> generated = (*it)->update(ticks);
			for (std::vector<VGameEntity*>::iterator it2 = generated.begin(); it2 != generated.end(); it2++) {
				newEnts.push_back((*it2));
			}
		}
		
		for (std::vector<VGameEntity*>::iterator it = newEnts.begin(); it != newEnts.end(); it++) {
			fEntities.push_back((*it));
		}
		
		for(std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end(); it++) {
			(*it)->visualize();
		}
	}
}
