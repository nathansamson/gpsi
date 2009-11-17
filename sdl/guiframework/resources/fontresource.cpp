#include <sstream>
#include "SDL_ttf.h"

#include "guiframework/resources/fontresource.h"



namespace sdlframework {
	FontResource* FontResource::open(std::string fontName, int size) {
		TTF_Font* font = TTF_OpenFont(fontName.c_str(), size);
		if (font != NULL) {
			std::stringstream ssFontID;
			ssFontID << font << "_" << size;
			std::string fontID;
			ssFontID >> fontID;

			return new FontResource(font, fontID);
		}
		return NULL;
	}

	FontResource::FontResource(TTF_Font* font, std::string name) : VResource(name), fFont(font) {
	}

	FontResource::~FontResource() {
		TTF_CloseFont(fFont);
		fFont = NULL;
	}

	SDL_Surface* FontResource::string(std::string text) {
		SDL_Color c = {0, 0, 0};
		return TTF_RenderText_Blended(fFont, text.c_str(), c);
	}
}
