#include "guiframework/resources/resource.h"

#include <iostream>

namespace sdlframework {

	VResource::VResource(std::string name) : fRefCount(1), fName(name) {
	}
	
	VResource::~VResource() {
	}

	std::string VResource::getName() {
		return fName;
	}
}
