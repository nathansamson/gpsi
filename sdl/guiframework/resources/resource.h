#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <string>

namespace sdlframework {
	class VResource {
	public:
		VResource(std::string);
		virtual ~VResource();
	
		//friend VResource* ResourceManager::GetResource(std::string);
		
		std::string getName();
	public:
		int fRefCount;
	private:
		VResource();
	
		std::string fName;
		
	};
}

#endif //_RESOURE_H_ 
