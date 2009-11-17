#ifndef _STRINGFONTRESOURCE_H_
#define _STRINGFONTRESOURCE_H_

#include "SDL.h"

#include "guiframework/resources/resource.h"

namespace sdlframework {
	class StringFontResource : public VResource {
	public:

		StringFontResource(SDL_Surface* surface, std::string name);
		virtual ~StringFontResource();

		int getWidth();
		int getHeight();
		
		SDL_Surface* getSurface();
	private:
		SDL_Surface* fSurface;
	};
}

#endif
