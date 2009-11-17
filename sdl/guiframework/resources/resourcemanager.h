#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include <map>

#include "guiframework/resources/resource.h"
#include "guiframework/resources/imageresource.h"
#include "guiframework/resources/fontresource.h"
#include "guiframework/resources/stringfontresource.h"

namespace sdlframework {
	class ResourceManager {
		public:
			static ResourceManager manager();
			
			void free(VResource* res);
			
			ImageResource* image(std::string);
			FontResource* font(std::string, int);
			StringFontResource* string(std::string, FontResource*);
		private:
			ResourceManager();
			
			bool hasResource(std::string);
			void insertResource(std::string, VResource*);
			VResource* getResource(std::string);
			
			std::map<std::string, VResource*> fResourceList;
			static ResourceManager fManager;
	};
}

#endif //_RESOURCEMANAGER_H_
