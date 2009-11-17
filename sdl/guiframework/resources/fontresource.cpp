#include <sstream>
#include "SDL_ttf.h"

#include "guiframework/resources/fontresource.h"



namespace sdlframework {
	FontResource* FontResource::open(std::string fontName, int size) {
		TTF_Font* font = TTF_OpenFont(fontName.c_str(), size);
		if (font != NULL) {
			return new FontResource(font, getID(fontName, size));
		}
		return NULL;
	}

	FontResource::FontResource(TTF_Font* font, std::string name)
	             : VResource(name), fFont(font) {
	}

	FontResource::~FontResource() {
		TTF_CloseFont(fFont);
		fFont = NULL;
	}

	SDL_Surface* FontResource::string(std::string text) {
		SDL_Color c = {0, 0, 0};
		return TTF_RenderText_Blended(fFont, text.c_str(), c);
	}

	std::string FontResource::getID(std::string fontName, int ptSize) {
		std::stringstream ssFontID;
		ssFontID << fontName << "_" << ptSize;
		std::string fontID;
		ssFontID >> fontID;
		return fontID;
	}
}
