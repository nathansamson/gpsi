/** \file
 * File for the game.
 *
 * @author Nathan Samson
*/

#include <stdexcept>

#include "game/game.h"
#include "game/levelreader.h"
#include "game/builtindriverfactory.h"
#include "misc/boundingbox.h"

namespace SI {
	/**
	 * Constructor.
	 *
	 * @param entityFactory The Entity factory for this game.
	 * @param levelDirectory The directory where to find levels.
	 * @param firstLevel The filename of the first level.
	 * @param gameVis The game visualizer.
	 * @param fac The factory to create drivers.
	*/
	Game::Game(IGameEntityFactory* entityFactory,
	           std::string levelDirectory, std::string firstLevel,
	           IGameVisualizer* gameVis, IDriverFactory* fac) 
	     : fEntityFactory(entityFactory), fDriverFactory(fac),
	       fWeaponery(new Weaponery()), fGameVisualizer(gameVis),
	       fLevelDirectory(levelDirectory) {
		
		fUserGroup = new EntityGroup("Users");
		fAIGroup = new EntityGroup("AI's");
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
				if ((*it)->isDead()) {
					continue;
				}
				for (std::list<VGameEntity*>::iterator it2 = it; it2 != fEntities.end(); it2++) {
					if (!(*it2)->isDead()) {
						if (*it2 != *it) {
							(*it)->checkCollision((*it2));
						}
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
			if ((!(*it)->isDead()) || (*it)->isVisible()) {
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
	
	/**
	 * Checks if the user is dead.
	 *
	 * @return True if the user loses, false if he is still alive.
	*/
	bool Game::isUserDead() {
		return (!hasShipsInGroup(fUserGroup) || enemyShipsCrossLine());
	}
	
	/**
	 * Checks if the AI is dead.
	 *
	 * @return True if the AI loses, false if he is still alive.
	*/
	bool Game::isAIDead() {
		return !hasEntitiesInGroup(fAIGroup);
	}
	
	/**
	 * Checks if the game is still running.
	 * When their are no new levels, and the user or the AI is dead this is false.
	 *
	 * @return True if the game is still running, false if not.
	*/
	bool Game::isPlaying() {
		return !((fCurrentLevel == "" && isAIDead()) || (isUserDead()));
	}
	
	/**
	 * Returns the score of the user player.
	 *
	 * @return The score of the user.
	*/
	int Game::getUserScore() {
		return fUserGroup->getScore();
	}
	
	/**
	 * Checks if the enemy ships crosses the 'user' line.
	 *
	 * @return True if the enemy crosses this line, false if not.
	*/
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
	
	/**
	 * Checks if a group has still ships.
	 *
	 * @param g The group.
	 *
	 * @return true if the group has still ships.
	*/
	bool Game::hasShipsInGroup(EntityGroup* g) {
		for(std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end(); it++) {
			if ((*it)->getGroup() == g && dynamic_cast<Ship*>(*it) != 0) {
				return true;
			}
		}
		return false;
	}
	
	/**
	 * Checks if a group has still entities.
	 *
	 * @param g The group.
	 *
	 * @return true if the group has still entities.
	*/
	bool Game::hasEntitiesInGroup(EntityGroup* g) {
		for(std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end(); it++) {
			if ((*it)->getGroup() == g) {
				return true;
			}
		}
		return false;
	}
	
	/**
	 * Start a new level.
	 *
	 * @param levelName The (file name) of the new level.
	*/
	void Game::startLevel(std::string levelName) {
		fWeaponery->clear();
		for (std::list<VGameEntity*>::iterator it = fEntities.begin(); it != fEntities.end(); it++) {
			delete (*it);
		}
		fEntities.clear();
		
		
		try {
			LevelReader level = LevelReader(fLevelDirectory+levelName, fEntityFactory, fDriverFactory, fWeaponery);
			fEntities.push_back(level.getUserShip(fUserGroup));
		
			std::vector<Ship*> ships = level.getEnemyShips(fAIGroup);
			for (std::vector<Ship*>::iterator it = ships.begin(); it != ships.end(); it++) {
				fEntities.push_back((*it));
			}
			fCurrentLevel = level.getLevelName();
			fNextLevel = level.getNextLevel();
		} catch (...) {
			throw std::runtime_error("Level file could not be loaded.");
		}
	}
}
