#include "bullet.h"
#include <SDL2/SDL.h>
#include <SDL2/extensions/SDL_image.h>
#include "gamesystem.h"
#include <math.h>


Bullet::Bullet(const char* src, int dir, int posx, int posy, int speedx, int speedy, const unsigned int* framecounter, SDL_Renderer* rp): 
direction(dir),
speedX(speedx+10), speedY(speedy), 
flying(true),
startingFrame(*framecounter), frameCounter(framecounter),
mainRendererPointer(rp),
srcRect(new SDL_Rect({50,10,5,5})), dstRect(new SDL_Rect({posx,posy,5,5})){
	createBullet(src);
}

Bullet::~Bullet(){
	destroyBullet();
}

void Bullet::createBullet(const char* src){
	SDL_Surface* temp_surf = IMG_Load(src);
	if(temp_surf!=(SDL_Surface*)0){
		texture = SDL_CreateTextureFromSurface(mainRendererPointer, temp_surf);
		SDL_FreeSurface(temp_surf);
	}else{
		GameSystem::writeErrorMessage(src);
	}
}

void Bullet::destroyBullet(){
	SDL_DestroyTexture(texture);
	delete srcRect;
	delete dstRect;
}

void Bullet::updateState(){
	if(*frameCounter-startingFrame>=120){
		flying = false;
	}else{
		if(*frameCounter%4==0){
			--speedX;
		}else;
		if(*frameCounter%3==0){
			--speedY;
		}else;	
	}
}

void Bullet::updateSprite(){
	int pm = GameSystem::PixToMetre;
	if(*frameCounter%7==0){
		++dstRect->w;
	}else;
	if(*frameCounter%10==0){
		++dstRect->h;
	}
	dstRect->x += speedX*direction*pm/60;
	dstRect->y += speedY*pm/60;
}

void Bullet::render(){	
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if(direction==-1){
		flip = SDL_FLIP_HORIZONTAL;
	}else;
	SDL_RenderCopyEx(mainRendererPointer, texture, srcRect, dstRect, 0, 0, flip);
}

bool Bullet::isFlying() const{
	return flying;
}
