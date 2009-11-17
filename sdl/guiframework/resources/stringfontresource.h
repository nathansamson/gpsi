#ifndef INC_STRINGFONTRESOURCE_H
#define INC_STRINGFONTRESOURCE_H

#include "SDL.h"

#include "guiframework/resources/resource.h"

namespace sdlframework {

	class FontResource;

	class StringFontResource : public VResource {
	public:

		StringFontResource(SDL_Surface*, std::string);
		virtual ~StringFontResource();

		int getWidth();
		int getHeight();
		
		SDL_Surface* getSurface();

		static std::string getID(std::string text, FontResource* font);
	private:
		SDL_Surface* fSurface;
	};
}

#endif // INC_STRINGFONTRESOURCE_H
