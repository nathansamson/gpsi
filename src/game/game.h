#ifndef INC_GAME_H
#define INC_GAME_H

#include <list>
#include <string>

#include "game/gameentityfactory.h"
#include "game/shipdriver.h"
#include "game/driverfactory.h"
#include "game/weaponery.h"
#include "game/gamevisualizer.h"

namespace SI {
	/**
	 * The Game class. All the logic of maintaining the state of the game,
	 * is included in this class.
	*/
	class Game {
	public:
		Game(IGameEntityFactory*, std::string, std::string,
		     IGameVisualizer*, IDriverFactory*);
		virtual ~Game();
		
		void update(int);
		
		bool isAIDead();
		bool isUserDead();
		
		bool isPlaying();
	private:
		bool hasEntitiesInGroup(EntityGroup*);
		void startLevel(std::string);
	
		/**
		 * A list of all entities in the game.
		*/
		std::list<VGameEntity*> fEntities;
		
		/**
		 * The entity factory to create the entities.
		*/
		IGameEntityFactory* fEntityFactory;
		
		/**
		 * The driver factory.
		*/
		IDriverFactory* fDriverFactory;
		
		/**
		 * The user group.
		*/
		EntityGroup* fUserGroup;
		
		/**
		 * The AI group.
		*/
		EntityGroup* fAIGroup;

		/**
		 * The weaponery.
		*/
		Weaponery* fWeaponery;
		
		/**
		 * The game visualizer.
		*/
		IGameVisualizer* fGameVisualizer;
		
		/**
		 * The directory of levels.
		*/
		std::string fLevelDirectory;
		
		/**
		 * The name of the current level.
		*/
		std::string fCurrentLevel;
		
		/**
		 * The filename of the next level.
		*/
		std::string fNextLevel;
	};
}

#endif // INC_GAME_H
