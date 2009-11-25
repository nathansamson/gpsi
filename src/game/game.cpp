#include "game.h"

namespace SI {
	Game::Game(VShipDriver* userShipDriver, IGameEntityFactory* entityFactory) : fEntityFactory(entityFactory) {
		Ship* user = entityFactory->createShip(userShipDriver);
		fEntities.push_back(user);
	}
	
	void Game::update(int ticks) {
		for(std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end(); it++) {
			(*it)->update(ticks);
		}
		
		for(std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end(); it++) {
			(*it)->visualize();
		}
	}
}
