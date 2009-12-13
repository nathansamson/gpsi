#ifndef INC_GAME_H
#define INC_GAME_H

#include <list>
#include "gameentityfactory.h"
#include "shipdriver.h"
#include "enemydriverfactory.h"

namespace SI {
	/**
	 * The Game class. All the logic of maintaining the state of the game,
	 * is included in this class.
	*/
	class Game {
	public:
		Game(VShipDriver*, IGameEntityFactory*, IEnemyDriverFactory* enemyDriverFactory);
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
	};
}

#endif // INC_GAME_H
