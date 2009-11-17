#ifndef INC_FONTRESOURCE_H
#define INC_FONTRESOURCE_H

#include "SDL_ttf.h"

#include "./guiframework/resources/resource.h"

namespace sdlframework {

	class FontResource : public VResource {
	public:
		virtual ~FontResource();

		static FontResource* open(std::string, int);
		SDL_Surface* string(std::string);
	private:
		TTF_Font* fFont;
		FontResource(TTF_Font*, std::string);
	};
}

#endif // INC_FONTRESOURCE_H
