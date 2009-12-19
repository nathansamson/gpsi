#include "game/game.h"
#include "game/levelreader.h"
#include "game/builtinenemydriverfactory.h"
#include "misc/boundingbox.h"

namespace SI {
	/**
	 * Constructor.
	 *
	 * @param userShipDriver The VShipDriver for the user ship.
	 * @param entityFactory The Entity factory for this game.
	 * @param enemyDriverFactory The factory to create enemy drivers.
	*/
	Game::Game(VShipDriver* userShipDriver, IGameEntityFactory* entityFactory,
	           std::string levelDirectory, std::string firstLevel,
	           IEnemyDriverFactory* fac) 
	     : fEntityFactory(entityFactory), fEnemyDriverFactory(fac), fWeaponery(new Weaponery()) {
	    LevelReader level = LevelReader(levelDirectory+firstLevel, entityFactory, fEnemyDriverFactory, fWeaponery);
		fUserGroup = new EntityGroup("Users");
		fEntities.push_back(level.getUserShip(userShipDriver, fUserGroup));
		
		fAIGroup = new EntityGroup("AI's");
		std::vector<Ship*> ships = level.getEnemyShips(fAIGroup);
		for (std::vector<Ship*>::iterator it = ships.begin(); it != ships.end(); it++) {
			fEntities.push_back((*it));
		}
	}
	
	Game::~Game() {
		for(std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end(); it++) {
			delete (*it);
		}
		delete fEntityFactory;
		delete fEnemyDriverFactory;
		delete fWeaponery;
		delete fUserGroup;
		delete fAIGroup;
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
				delete (*it);
				fEntities.erase(it);
			}
			it = next;
		}
	}
	
	bool Game::isUserDead() {
		return !hasEntitiesInGroup(fUserGroup);
	}
	
	bool Game::isAIDead() {
		return !hasEntitiesInGroup(fAIGroup);
	}
	
	bool Game::hasEntitiesInGroup(EntityGroup* g) {
		for(std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end(); it++) {
			if ((*it)->getGroup() == g) {
				return true;
			}
		}
		return false;
	}
}
