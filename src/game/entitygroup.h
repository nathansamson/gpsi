#ifndef INC_ENTITYGROUP_H
#define INC_ENTITYGROUP_H

#include <string>

namespace SI {
	/**
	 * Class that represents a group of entities.
	*/
	class EntityGroup {
	public:
		EntityGroup(std::string);
		
		std::string getName();
	private:
		/**
		 * The name of the group.
		*/
		std::string fName;
	};
}

#endif // INC_ENTITYGROUP_H
