#include "game.h"
#include "misc/boundingbox.h"

namespace SI {
	/**
	 * Constructor.
	 *
	 * @param userShipDriver The VShipDriver for the user ship.
	 * @param entityFactory The Entity factory for this game.
	 * @param enemyDriverFactory The factory to create enemy drivers.
	*/
	Game::Game(VShipDriver* userShipDriver, IGameEntityFactory* entityFactory, IEnemyDriverFactory* enemyDriverFactory) 
	     : fEntityFactory(entityFactory), fEnemyDriverFactory(enemyDriverFactory) {
	    EntityGroup* users = new EntityGroup("Users");
	    ShipType userShipType;
	    userShipType.fBoundingShapeDesc = new BoundingBoxDescription(0.80, 0.56);
	    userShipType.fName = "X Wing";
		Ship* user = entityFactory->createShip(userShipDriver, Vector2(0.0, -2.0), 0, users, userShipType);
		delete userShipType.fBoundingShapeDesc;
		fEntities.push_back(user);
		
		EntityGroup* ais = new EntityGroup("AI's");
		ShipType enemyShipType;
	    enemyShipType.fName = "Obi-Wan_starfighter";
	    enemyShipType.fBoundingShapeDesc = new BoundingBoxDescription(0.80, 0.80);
		for (int i = 0; i < 5; i++) {
			fEntities.push_back(entityFactory->createShip(
			            enemyDriverFactory->createEnemyDriver(),
			            Vector2(-4.0+(i+1)*8.0/6, 2.5), 180, ais, enemyShipType));
		}
		delete enemyShipType.fBoundingShapeDesc;
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
		
		for(std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end(); it++) {
			for (std::list<VGameEntity*>::iterator it2 = it; it2 != fEntities.end(); it2++) {
				if (it != it2) {
					(*it)->checkCollision((*it2));
				}
			}
		}
		
		for (std::vector<VGameEntity*>::iterator it = newEnts.begin(); it != newEnts.end(); it++) {
			fEntities.push_back((*it));
		}
		
		for(std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end();) {
			std::list<VGameEntity*>::iterator next = it;
			next++;
			if (!(*it)->isDead()) {
				(*it)->visualize();
			} else {
				fEntities.erase(it);
			}
			it = next;
		}
	}
}
