#ifndef _IMAGERESOURCE_H_
#define _IMAGERESOURCE_H_

#include <SDL/SDL.h>

#include "guiframework/resources/resource.h"

namespace sdlframework {
	class ImageResource : public VResource {
	public:
		static ImageResource* open(std::string);
		
		int getWidth();
		int getHeight();
		
		SDL_Surface* getSurface();
	private:
		ImageResource();
		ImageResource(std::string, SDL_Surface*);
		virtual ~ImageResource();
	
		SDL_Surface* fImageSurface;
	};
}

#endif // _IMAGERESOURCE_H_
