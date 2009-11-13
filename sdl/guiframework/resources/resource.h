#ifndef _RESOURCE_H_
#define _RESOURCE_H_

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

#endif //_RESOURE_H_ 
