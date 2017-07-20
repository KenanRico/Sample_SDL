#include "tileset.h"
#include <SDL2/SDL.h>
#include <string>


TileSet::TileSet(SDL_Renderer* renderer, const char* _name, const char* _source, int firstID, int twidth, int theight, int count, int _columns):
texture((SDL_Texture*)0), name(_name), source(_source), firstgid(firstID), tilewidth(twidth), tileheight(theight), tilecount(count), columns(_columns){
	SDL_Surface* surf = IMG_Load(_source);
	texture = SDL_GetTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	lastgid = firstgid + tilecount - 1;
	rows = tilecount/columns;
}

TileSet::~TileSet(){
	SDL_DestroyTexture(texture);
}


int TileSet::getFirstTileID() const{
	return firstgid;
}
int TileSet::getLastTileID() const{
	return lastgid;
}

SDL_Texture* TileSet::getTexture() const{
	return texture;
}
