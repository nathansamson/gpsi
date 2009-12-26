/** \file
 * File for the entity group.
 *
 * @author Nathan Samson
*/

#include "game/entitygroup.h"

namespace SI {
	/**
	 * Constructor.
	 *
	 * @param name The name of the group.
	*/
	EntityGroup::EntityGroup(std::string name): fName(name), fScore(0) {
	}
	
	/**
	 * Returns the name of the group.
	 *
	 * @return The name of the group.
	*/
	std::string EntityGroup::getName() {
		return fName;
	}
	
	/**
	 * Returns the score of the group.
	 *
	 * @return the score of the group.
	*/
	int EntityGroup::getScore() {
		return fScore;
	}
	
	/**
	 * Increase (or decrease) the score of the group.
	 *
	 * @param update The change.
	*/
	void EntityGroup::increaseScore(int update) {
		fScore += update;
	}
}
