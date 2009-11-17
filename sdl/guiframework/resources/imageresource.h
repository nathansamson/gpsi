#ifndef INC_IMAGERESOURCE_H
#define INC_IMAGERESOURCE_H

#include "SDL.h"

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

#endif // INC_IMAGERESOURCE_H
