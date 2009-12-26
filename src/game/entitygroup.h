#ifndef INC_ENTITYGROUP_H
#define INC_ENTITYGROUP_H

/** \file
 * File for the entity group.
 *
 * @author Nathan Samson
*/

#include <string>

namespace SI {
	/**
	 * Class that represents a group of entities.
	*/
	class EntityGroup {
	public:
		EntityGroup(std::string);
		
		std::string getName();
		void increaseScore(int);
		int getScore();
	private:
		/**
		 * The name of the group.
		*/
		std::string fName;
		
		/**
		 * The score of the group.
		*/
		int fScore;
	};
}

#endif // INC_ENTITYGROUP_H
