#ifndef INC_GAME_H
#define INC_GAME_H

#include <list>
#include <string>

#include "game/gameentityfactory.h"
#include "game/shipdriver.h"
#include "game/builtinenemydriverfactory.h"
#include "game/weaponery.h"

namespace SI {
	/**
	 * The Game class. All the logic of maintaining the state of the game,
	 * is included in this class.
	*/
	class Game {
	public:
		Game(VShipDriver*, IGameEntityFactory*, std::string, std::string, IEnemyDriverFactory* = new BuiltinEnemyDriverFactory());
		virtual ~Game();
		
		void update(int);
		
		bool isAIDead();
		bool isUserDead();
	private:
		bool hasEntitiesInGroup(EntityGroup*);
	
		/**
		 * A list of all entities in the game.
		*/
		std::list<VGameEntity*> fEntities;
		
		/**
		 * The entity factory to create the entities.
		*/
		IGameEntityFactory* fEntityFactory;
		
		/**
		 * The enemy driver factory.
		*/
		IEnemyDriverFactory* fEnemyDriverFactory;
		
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
	};
}

#endif // INC_GAME_H
