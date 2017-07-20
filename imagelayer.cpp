#include "imagelayer.h"

#include <SDL2/SDL.h>
#include <string>



ImageLayer::ImageLayer(const char* _name, const char* _source, int w, int h, int offx, int offy, SDL_Renderer* renderer, SDL_Window* window):
name(_name), source(_source), width(w), height(h), offsetx(offx), offsety(offy), mainRendererPointer(renderer), mainWindowPointer(window)
texture((SDL_Texture*)0), srcRect((SDL_Rect*)0), dstRect((SDL_Rect*)0){
	initImageLayer();
}
ImageLayer::~ImageLayer(){
	destroyImageLayer();
}


void ImageLayer::initImageLayer(){
	SDL_Surface* surf = IMG_Load(source.c_str());
	if(surf!=(SDL_Surface*)0){
		texture = SDL_CreateTextureFromSurface(surf);
	}else;
	SDL_FreeSurface(surf);

	int windowW = 0;
	int windowH = 0;
	SDL_GetWindowSize(mainWindowPointer, &windowW, &windowH);
	srcRect = new SDL_Rect(offsetx, offsety, windowW, windowH)
	dstRect = new SDL_Rect(0, 0, windowW, windowH);
}
void ImageLayer::destroyImageLayer(){
	SDL_DestroyTexture(texture);
	delete srcRect;
	delete dstRect;
}


void ImageLayer::updateImageLayer(){





}

void ImageLayer::renderImageLayer(){
	SDL_RenderCopy(mainRendererPointer, texutre, srcRect, dstRect);
}
