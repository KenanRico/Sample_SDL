#include "tileset.h"
#include <SDL2/SDL.h>
#include <SDL2/extensions/SDL_image.h>
#include <string>
#include "gamesystem.h"

#include <iostream>//remove


TileSet::TileSet(SDL_Renderer* renderer, const char* _name, const char* _source, int firstID, int twidth, int theight, int count, int _columns):
texture((SDL_Texture*)0), name(_name), source(_source), firstgid(firstID), tilewidth(twidth), tileheight(theight), tilecount(count), columns(_columns){
	SDL_Surface* surf = IMG_Load(_source);
	if(surf!=(SDL_Surface*)0){
		texture = SDL_CreateTextureFromSurface(renderer, surf);
	}else{
		GameSystem::writeErrorMessage("TileSet: Failed to load image");
	}
	SDL_FreeSurface(surf);
	lastgid = firstgid + tilecount - 1;
	rows = tilecount/columns;
}

TileSet::~TileSet(){
	SDL_DestroyTexture(texture);
}

int TileSet::columnCount() const{
	return columns;
}

