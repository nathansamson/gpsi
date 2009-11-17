#include "guiframework/resources/resource.h"

#include <iostream>

namespace sdlframework {

	VResource::VResource(std::string name)
	          : fName(name), fRefCount(1) {
	}
	
	VResource::~VResource() {
	}

	std::string VResource::getName() {
		return fName;
	}
}
