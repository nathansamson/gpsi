#ifndef _FONTRESOURCE_H_
#define _FONTRESOURCE_H_

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

#endif // _FONTRESOURCE_H_
