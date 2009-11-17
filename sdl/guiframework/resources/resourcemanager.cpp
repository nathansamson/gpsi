#include "guiframework/resources/resourcemanager.h"

namespace sdlframework {
	ResourceManager::ResourceManager() {
	}

	ResourceManager ResourceManager::manager() {
		return ResourceManager::fManager;
	}
	
	void ResourceManager::free(VResource* res) {
		res->fRefCount--;
		
		if (res->fRefCount == 0) {
			fResourceList.erase(res->getName());
			delete res;
			res = NULL;
		}
	}
	
	ImageResource* ResourceManager::image(std::string name) {
		if (!hasResource(name)) {
			ImageResource* res = ImageResource::open(name);
			insertResource(name, res);
			
			return res;
		} else {
			return static_cast<ImageResource*>(getResource(name));
		}
	}
	
	bool ResourceManager::hasResource(std::string name) {
		return fResourceList.find(name) != fResourceList.end();
	}
	
	void ResourceManager::insertResource(std::string name, VResource* res) {
		fResourceList[name] = res;
	}
	
	VResource* ResourceManager::getResource(std::string name) {
		VResource* res = fResourceList[name];
		res->fRefCount++;
		return res;
	}
	
	ResourceManager ResourceManager::fManager = ResourceManager();
}
