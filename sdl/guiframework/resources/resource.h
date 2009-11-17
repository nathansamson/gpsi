#ifndef INC_RESOURCE_H
#define INC_RESOURCE_H

#include <string>

namespace sdlframework {

	class VResource {
	public:
		VResource(std::string);
		virtual ~VResource();

		friend class ResourceManager;

		std::string getName();
	private:
		VResource();

		std::string fName;
		int fRefCount;
	};
}

#endif // INC_RESOURE_H
