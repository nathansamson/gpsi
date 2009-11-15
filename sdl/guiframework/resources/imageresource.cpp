#include "SDL.h"

#include "guiframework/resources/imageresource.h"

namespace sdlframework {

	ImageResource::ImageResource(std::string name, SDL_Surface* surface) : VResource(name), fImageSurface(surface) {
	}
	
	ImageResource::~ImageResource() {
		SDL_FreeSurface(fImageSurface);
	}

	ImageResource* ImageResource::open(std::string name) {
		SDL_Surface* temp;
		SDL_Surface* image;
		
		temp = SDL_LoadBMP(("../data/"+name).c_str());
		if (temp == NULL) {
			// What to do now?
			return NULL;
		}
		
		image = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);
		return new ImageResource(name, image);
	}
	
	int ImageResource::getWidth() {
		return fImageSurface->w;
	}
	
	int ImageResource::getHeight() {
		return fImageSurface->h;
	}
	
	SDL_Surface* ImageResource::getSurface() {
		return fImageSurface;
	}

}
