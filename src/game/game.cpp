#include "game/game.h"
#include "game/levelreader.h"
#include "game/builtindriverfactory.h"
#include "misc/boundingbox.h"

namespace SI {
	/**
	 * Constructor.
	 *
	 * @param userShipDriver The VShipDriver for the user ship.
	 * @param entityFactory The Entity factory for this game.
	 * @param enemyDriverFactory The factory to create enemy drivers.
	*/
	Game::Game(IGameEntityFactory* entityFactory,
	           std::string levelDirectory, std::string firstLevel,
	           IGameVisualizer* gameVis, IDriverFactory* fac) 
	     : fEntityFactory(entityFactory), fDriverFactory(fac),
	       fWeaponery(new Weaponery()), fGameVisualizer(gameVis),
	       fLevelDirectory(levelDirectory) {
		
		startLevel(firstLevel);
	}
	
	Game::~Game() {
		for(std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end(); it++) {
			delete (*it);
		}
		delete fEntityFactory;
		delete fDriverFactory;
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
		if (fGameVisualizer->inNonGamePhase()) {
			fGameVisualizer->draw();
			return;
		}
		
		if (ticks != 0) {	
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
		
		if (isUserDead()) {
			fGameVisualizer->userDies();
		} else if (isAIDead()) {
			if (fNextLevel != "") {
				startLevel(fNextLevel);
				fGameVisualizer->levelChange(fCurrentLevel);
			} else {
				fCurrentLevel = "";
				fGameVisualizer->userWins();
			}
		}
		fGameVisualizer->draw();
	}
	
	bool Game::isUserDead() {
		return (!hasShipsInGroup(fUserGroup) || enemyShipsCrossLine());
	}
	
	bool Game::isAIDead() {
		return !hasEntitiesInGroup(fAIGroup);
	}
	
	bool Game::isPlaying() {
		return !((fCurrentLevel == "" && isAIDead()) || (isUserDead()));
	}
	
	bool Game::enemyShipsCrossLine() {
		for(std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end(); it++) {
			if ((*it)->getGroup() == fAIGroup && dynamic_cast<Ship*>(*it) != 0) {
				if ((*it)->crossesLine(-1.5)) {
					return true;
				}
			}
		}
		return false;
	}
	
	bool Game::hasShipsInGroup(EntityGroup* g) {
		for(std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end(); it++) {
			if ((*it)->getGroup() == g && dynamic_cast<Ship*>(*it) != 0) {
				return true;
			}
		}
		return false;
	}
	
	bool Game::hasEntitiesInGroup(EntityGroup* g) {
		for(std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end(); it++) {
			if ((*it)->getGroup() == g) {
				return true;
			}
		}
		return false;
	}
	
	void Game::startLevel(std::string levelName) {
		fWeaponery->clear();
		for (std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end(); it++) {
			delete (*it);
		}
		fEntities.clear();
		
		
		LevelReader level = LevelReader(fLevelDirectory+levelName, fEntityFactory, fDriverFactory, fWeaponery);
		fUserGroup = new EntityGroup("Users");
		fEntities.push_back(level.getUserShip(fUserGroup));
		
		fAIGroup = new EntityGroup("AI's");
		std::vector<Ship*> ships = level.getEnemyShips(fAIGroup);
		for (std::vector<Ship*>::iterator it = ships.begin(); it != ships.end(); it++) {
			fEntities.push_back((*it));
		}
		fCurrentLevel = level.getLevelName();
		fNextLevel = level.getNextLevel();
	}
}
