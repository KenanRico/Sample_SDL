#include <SDL2/SDL.h>
#include "sprite.h"

Sprite::~Sprite(){
	//free resources
	destroySprite();
}

Sprite::Sprite(const Sprite& rhs) : s_sourceImage(rhs.s_sourceImage){
	createSprite();	
}


Sprite::Sprite(const char* img) : s_sourceImage(img){


}

SDL_Rect Sprite::getSourceRectangle(){
	return s_srcRect;
}

SDL_Rect Sprite::getDestinationRectangle(){
	return s_dstRect;
}


void Sprite::createSprite(){


}

void Sprite::destroySprite(){


}




