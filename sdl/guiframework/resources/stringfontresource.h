#ifndef INC_STRINGFONTRESOURCE_H
#define INC_STRINGFONTRESOURCE_H

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

#endif // INC_STRINGFONTRESOURCE_H
