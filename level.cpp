#include <SDL2/SDL.h>
#include <string>
#include <vector>
//#include "layer.h"
//#include "tileset.h"
//#include "imagelayer.h"
#include "gamesystem.h"
#include "xmlparser.h"

Level::Level(const char* tilemap_path, SDL_Renderer* g_renderer, SDL_Window* g_window): lv_name(tilemap_path), lv_mapH(0), lv_mapW(0), lv_tileH(0), lv_tileW(0), lv_complete(false), mainRendererPointer(g_renderer), mainWindowPointer(g_window){
	if(initLevel()){
		std::string Msg1 = "Inited level: ";
		std::string Msg = Msg1 + std::string(lv_name);
		GameSystem::writeMessage(Msg.c_str());
	}else{
		std::string Err1 = "Failed to init level: ";
		std::string Err = Err1 + std::string(lv_name);
		GameSystem::writeErrorMessage(Msg.c_str());
	}
}
Level::~Level(){
	destroyLevel();
}


bool Level::initLevel(){
	XMLParser::TileMap(lv_name.c_str(), lv_layers, lv_imagelayers, lv_tilesets);
}
bool Level::destroyLevel(){
	for(std::vector<TileLayer*>::iterator i=lv_layers.begin(); i<lv_layers.end(); ++i){
		delete *i;
	}
	for(std::vector<TileSet*>::iterator i=lv_tilesets.begin(); i<lv_tilesets.end(); ++i){
		delete *i;
	}
}


int** Level::overallTileLayer(){
	//allocate array[mapH][mahW] to all 0s
	int** finalLayer = new int*[lv_mapH]();
	for(int i=0; i<mapH; ++i){
		finalLayer[i] = new int[lv_mapW]();
	}
	//from upper layer to lower layer, put non-zero values in
	for(std::vector<TileLayer*>::const_iterator iter=lv_layers.begin(); iter<lv_layers.end(); ++iter){
		for(int i=0; i<lv_mapH; ++i){
			for(int j=0; j<lv_mapW; ++j){
				if(finalLayer[i][j]==0)
					finalLayer[i][j] = iter->getTileID(i,j);
				}else;
			}
		}
	}
	return finalLayer;
}

SDL_Texture Level::getTextureFromTileID(int tileID){
	//return a texture from given tile ID
	try{
		if(tileID<1){
			std::string Err("tileID out of range");
			throw Err.c_str();
		}else{
			std::vector<TileSet*>::const_iterator i=lv_tilesets.begin();
			while(tileID > i->geLastTileID()){
				++i;
			}
			if(i>=lv_tilesets.end()){
				std::string Err("tileID out of range");
				throw Err.c_str();
			}else{
				lv_srcRect->h = i->getTileH();
				lv_srcRect->w = i->getTileW();
				lv_srcRect->y = lv_srcRect->h * ((tileID-1) / i->columnCount());
				lv_srcRect->x = lv_srcRect->w * ((tileID-1) % i->columnCount());
				return i->getTexture();
			}
		}
	}catch(const char* Err){
		throw Err;
	}
	return (SDL_Texture*)0;
}

void Level::drawBackground(){


}


void Level::updateLevel(){
	//update level graphics



}
void Level::renderLevel(){
	int windowH = 0;
	int windowW = 0;	
	SDL_GetWindowSize(mainWindowPointer, &windowW, &windowH);
	lv_dstRect->h = windowH/mapH;
	lv_dstRect->w = windowW/mapW;

	int** map = overallTileLayer(); //final array(mapH*mapW) of data encoding of all tile layers combined
	for(int i=0; i<mapH; ++i){
		lv_dstRect->y = i*lv_dstRect->h;
		for(int j=0; j<mapW; ++j){
			lv_dstRect->x += j*lv_dstRect->w;
			int tileID = map[i][j];
			SDL_Texture* box = (SDL_Texture*)0;
			try{
				box = getTextureFromTileID(tileID);
			}catch(const char* Err){
				GameSystem::writeErrorMessage(Err);
				return;
			}
			drawBackground();
			SDL_RenderCopy(mainRendererPointer, box, lv_srcRect, lv_dstRect);
			SDL_DestroyTexture(box);
		}
	}

	for(int i=0; i<lv_tileH; ++i){
		delete[] map[i];
	}
	delete[] map;
}


bool Level::isComplete(){
	return lv_complete;
}
