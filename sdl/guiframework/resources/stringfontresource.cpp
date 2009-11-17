#include "guiframework/resources/stringfontresource.h"

namespace sdlframework {

	StringFontResource::StringFontResource(SDL_Surface* surface, std::string name)
	                   : VResource(name), fSurface(surface) {
	}

	StringFontResource::~StringFontResource() {
		SDL_FreeSurface(fSurface);
	}
	
	int StringFontResource::getWidth() {
		return fSurface->w;
	}
	
	int StringFontResource::getHeight() {
		return fSurface->h;
	}
	
	SDL_Surface* StringFontResource::getSurface() {
		return fSurface;
	}

}
