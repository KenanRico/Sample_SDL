#include <SDL2/SDL.h>
#include <SDL2/extensions/SDL_image.h>
#include "sprite.h"
#include "gamesystem.h"
#include <string>


Sprite::~Sprite(){
	destroySprite();
}

/*Sprite::Sprite(const Sprite& rhs) : s_mainRendererPointer(rhs.s_mainRendererPointer), s_sourceImage(rhs.s_sourceImage), s_created(false){
}*/


Sprite::Sprite(SDL_Renderer* g_renderer, const char* img, int _sx, int _sy, int _sw, int _sh, int _dx, int _dy, int _dw, int _dh) :
s_mainRendererPointer(g_renderer),
s_sourceImage(img),
s_srcRect(new SDL_Rect{_sx,_sy,_sw,_sh}),
s_dstRect(new SDL_Rect{_dx,_dy,_dw,_dh}),
s_imageW(0),
s_imageH(0),
s_created(false),
s_framecounter(0){
	;
}

void Sprite::createSprite(){
	if(s_created){
		std::string Err1("Already created sprite with image: ");
		std::string Err = Err1+s_sourceImage;
		GameSystem::writeErrorMessage(Err.c_str());
		return;
	}else;
	SDL_Surface* temp_surf = IMG_Load(s_sourceImage.c_str());
	if(temp_surf!=(SDL_Surface*)0){
		s_texture = SDL_CreateTextureFromSurface(s_mainRendererPointer, temp_surf);
	}else{
		std::string Err1("Failed to load image: ");
		std::string Err = Err1+s_sourceImage;
		GameSystem::writeErrorMessage(Err.c_str());
	}
	SDL_FreeSurface(temp_surf);
	if(s_texture!=(SDL_Texture*)0){
		SDL_QueryTexture(s_texture, 0, 0, &s_imageW, &s_imageH);
	}else{
		GameSystem::writeErrorMessage("Failed to retrieve width and heights of image: s_texture is nullptr");
	}
	s_created = true;
	GameSystem::writeMessage("Initialized sprite");
}

void Sprite::destroySprite(){
	SDL_DestroyTexture(s_texture);
	delete s_srcRect;
	delete s_dstRect;
	GameSystem::writeMessage("Destroyed sprite");
}


void Sprite::setSrcRect(int x, int y, int w, int h){
	s_srcRect->x = x;
	s_srcRect->y = y;
	s_srcRect->w = w;
	s_srcRect->h = h;
}
void Sprite::setDstRect(int x, int y, int w, int h){
	s_dstRect->x = x;
	s_dstRect->y = y;
	s_dstRect->w = w;
	s_dstRect->h = h;
}

void Sprite::resetFrameCounter(){
	s_framecounter = 0;
}

/*void Sprite::moveRight(){
	int w = 300;
	int h = 0;
	std::cout<<s_srcRect->x<<std::endl;
	SDL_QueryTexture(s_texture, nullptr, nullptr, &w, &h);
	s_srcRect->x = (s_srcRect->x+40>w)?3:s_srcRect->x+40;
	s_dstRect->x += 4;
}*/

/*void Sprite::render(){
	SDL_RenderCopyEx(*s_mainRendererPointer, s_texture, s_srcRect, s_dstRect, 0, 0, SDL_FLIP_NONE);
	SDL_Delay(10);
}*/
