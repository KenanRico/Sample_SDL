#include <SDL2/SDL.h>
#include "sprite.h"
#include "gamesystem.h"
#include <string>


Sprite::~Sprite(){
	destroySprite();
}

Sprite::Sprite(const Sprite& rhs) : s_mainRendererPointer(rhs.s_mainRendererPointer), s_sourceImage(rhs.s_sourceImage), s_created(false){
}


Sprite::Sprite(SDL_Renderer*& g_renderer, const char* img) : s_mainRendererPointer(&g_renderer), s_sourceImage(img), s_created(false){

}

SDL_Texture* Sprite::getTexturePtr(){
	return s_texture;
}

SDL_Rect* Sprite::getSourceRectanglePtr(){
	return &s_srcRect;
}

SDL_Rect* Sprite::getDestinationRectPtr(){
	return &s_dstRect;
}

void Sprite::moveRight(){
	
	s_dstRect.x += 5;


}


void Sprite::createSprite(){
	if(s_created){
		std::string Err1("Already created sprite with BMP: ");
		std::string Err = Err1+s_sourceImage;
		GameSystem::writeErrorMessage(Err.c_str());
		return;
	}else;
	SDL_Surface* temp_surf = SDL_LoadBMP(s_sourceImage.c_str());
	if(temp_surf!=(SDL_Surface*)0){
		s_texture = SDL_CreateTextureFromSurface(*s_mainRendererPointer, temp_surf);	
	}else{
		std::string Err1("Failed to load bmp: ");
		std::string Err = Err1+s_sourceImage;
		GameSystem::writeErrorMessage(Err.c_str());
	}
	SDL_FreeSurface(temp_surf);
	if(s_texture!=(SDL_Texture*)0){
		SDL_QueryTexture(s_texture, 0, 0, &s_imageW, &s_imageH);
	}else{
		GameSystem::writeErrorMessage("Failed to retrieve width and heights of image: s_texture is nullptr");
	}
	//-------below init for rectangles are temporary-------------	
	s_srcRect.x = 0;
	s_srcRect.y = 0;
	s_srcRect.w = s_imageW;
	s_srcRect.h = s_imageH;
	s_dstRect.x = 100;
	s_dstRect.y = 100;	
	s_dstRect.w = s_srcRect.w;
	s_dstRect.h = s_srcRect.h;
	//-----------------------------------------------------------
	s_created = true;
	GameSystem::writeMessage("Initialized sprite");
}

void Sprite::destroySprite(){
	SDL_DestroyTexture(s_texture);

	GameSystem::writeMessage("Destroyed sprite");
}



