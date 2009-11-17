#include "guiframework/resources/stringfontresource.h"
#include "guiframework/resources/fontresource.h"

namespace sdlframework {

	StringFontResource::StringFontResource(SDL_Surface* surface, std::string id)
	                   : VResource(id), fSurface(surface) {
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

	std::string StringFontResource::getID(std::string text, FontResource* font) {
		return text + font->getName();
	}

}
