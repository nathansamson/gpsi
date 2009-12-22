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
	
	int EntityGroup::getScore() {
		return fScore;
	}
	
	void EntityGroup::increaseScore(int update) {
		fScore += update;
	}
}
