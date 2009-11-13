#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include <map>

#include "guiframework/resources/resource.h"
#include "guiframework/resources/imageresource.h"

namespace sdlframework {
	class ResourceManager {
		public:
			static ResourceManager manager();
			
			void free(VResource* res);
			
			ImageResource* image(std::string name);
		private:
			ResourceManager();
			
			bool HasResource(std::string);
			void InsertResource(std::string, VResource*);
			VResource* GetResource(std::string);
			
			std::map<std::string, VResource*> fResourceList;
			static ResourceManager fManager;
	};
}

#endif //_RESOURCEMANAGER_H_
