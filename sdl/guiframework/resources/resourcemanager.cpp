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

	FontResource* ResourceManager::font(std::string name, int a) {
		if (!hasResource(name)) {
			FontResource* font = FontResource::open(name, a);
			insertResource(name, font);
			
			return font;
		} else {
			return static_cast<FontResource*>(getResource(name));
		}
	}

	StringFontResource* ResourceManager::string(std::string text, FontResource* font) {
		if (!hasResource(text)) {
			SDL_Surface* surf = font->string(text);
			StringFontResource* p = new StringFontResource(surf, text);
			insertResource(p->getName(), p);
			
			return p;
		} else {
			return static_cast<StringFontResource*>(getResource(text));
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
