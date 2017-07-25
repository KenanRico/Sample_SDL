#include "level.h"
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <sstream>
#include "tilelayer.h"
#include "tileset.h"
#include "imagelayer.h"
#include "gamesystem.h"
#include "sprite_player.h"
#include "xmlparser.h"

#include <iostream>//remove



Level::Level(const char* tilemap_dir, const char* tilemap_file, SDL_Renderer* g_renderer, SDL_Window* g_window, const Player* player): 
lv_dir(tilemap_dir), lv_file(tilemap_file), 
lv_overallTileLayer((int***)0),
lv_mapH(0), lv_mapW(0), lv_tileH(0), lv_tileW(0), lv_complete(false), 
lv_mainRendererPointer(g_renderer), lv_texture((SDL_Texture*)0), lv_mainWindowPointer(g_window), lv_playerPointer(player),
lv_srcRect(new SDL_Rect({0,0,0,0})), lv_dstRect(new SDL_Rect({0,0,0,0})){
	initLevel();
}
Level::~Level(){
	destroyLevel();
}


void Level::initLevel(){
	XMLParser::TileMap(lv_dir.c_str(), lv_file.c_str(), lv_layers, lv_imagelayers, lv_tilesets, lv_mapH, lv_mapW, lv_tileH, lv_tileW, lv_mainRendererPointer, lv_mainWindowPointer);
	setOverallTileLayer();
}
void Level::destroyLevel(){
	for(std::vector<TileLayer*>::iterator i=lv_layers.begin(); i<lv_layers.end(); ++i){
		delete *i;
	}
	for(std::vector<ImageLayer*>::iterator i=lv_imagelayers.begin(); i<lv_imagelayers.end(); ++i){
		delete *i;
	}
	for(std::vector<TileSet*>::iterator i=lv_tilesets.begin(); i<lv_tilesets.end(); ++i){
		delete *i;
	}
	for(int i=0; i<lv_mapH; ++i){
		for(int j=0; j<lv_mapW; ++j){
			delete[] lv_overallTileLayer[i][j];
		}
		delete[] lv_overallTileLayer[i];
	}
	delete[] lv_overallTileLayer;
	delete lv_srcRect;
	delete lv_dstRect;
}


void Level::setOverallTileLayer() const{

	unsigned int layers_count = lv_layers.size();
	//allocate array[mapH][mahW] to all 0s
	lv_overallTileLayer = new int**[lv_mapH]();
	for(int i=0; i<lv_mapH; ++i){
		lv_overallTileLayer[i] = new int*[lv_mapW]();
		for(int j=0; j<lv_mapW; ++j){
			lv_overallTileLayer[i][j] = new int[layers_count]();
		}
	}
	//from upper layer to lower layer, put non-zero values in
	for(unsigned int layer=0; layer<layers_count; ++layer){
		const TileLayer* CurrentLayer = lv_layers[layer];
		int rows = CurrentLayer->getTileLayerH();
		int cols = CurrentLayer->getTileLayerW();	
		for(int i=0; i<rows; ++i){
			for(int j=0; j<cols; ++j){
				int tileID = CurrentLayer->getTileID(i,j);
				lv_overallTileLayer[i][j][layer] = CurrentLayer->getTileID(i,j);
			}
		}
	}
//	for(int i=0; i<lv_mapH; ++i){
//		for(int j=0; j<lv_mapW; ++j){
//			std::cout<<finalLayer[i][j]<<" ";
//		}
//		std::cout<<"\n";
//	}
//	return finalLayer;
}

bool Level::setSrcRectFromTileID(int tileID) const{
	//return a lv_texture from given tile ID
	bool result = false;
	if(tileID<1){
		//nothing to draw
	}else{
		try{
			std::vector<TileSet*>::const_iterator i=lv_tilesets.begin();
			while(tileID > (*i)->getLastTileID()){
				++i;
			}
			if(i>=lv_tilesets.end()){
				std::stringstream ss;
				ss<<"tileID our of range: "<<tileID;
				throw ss.str().c_str();	
			}else{
				lv_srcRect->h = (*i)->getTileH();
				lv_srcRect->w = (*i)->getTileW();
				lv_srcRect->y = lv_srcRect->h * ((tileID-(*i)->getFirstTileID()) / (*i)->columnCount());
				lv_srcRect->x = lv_srcRect->w * ((tileID-(*i)->getFirstTileID()) % (*i)->columnCount());
				lv_texture = (*i)->getTexture();
				result = true;
			}
		}catch(const char* Err){
			GameSystem::writeErrorMessage(Err);
		}
	}
	return result;
}

void Level::drawBackground() const{
	for(std::vector<ImageLayer*>::const_iterator iter=lv_imagelayers.end()-1; iter>=lv_imagelayers.begin(); --iter){
		(*iter)->renderImageLayer();
	}
}


void Level::updateLevel() const{
	int windowH = 0;
	int windowW = 0;	
	SDL_GetWindowSize(lv_mainWindowPointer, &windowW, &windowH);
	//lv_dstRect->h = windowH / lv_mapH;
	//lv_dstRect->w = windowW / lv_mapW;
	
	lv_dstRect->h = windowH / (GameSystem::defaultWindowH / lv_tileH);
	lv_dstRect->w = windowW / (GameSystem::defaultWindowW / lv_tileW);
	for(std::vector<ImageLayer*>::const_iterator iter=lv_imagelayers.end()-1; iter>=lv_imagelayers.begin(); --iter){
		(*iter)->updateImageLayer(windowW, windowH);
	}
}
void Level::renderLevel() const{
	//set lv_srcRect according to character's position relative to whole map.
	//int characterX = lv_playerPointer->getX();
	//int characterY = lv_playerPointer->getY();
	int characterX = lv_playerPointer->getOffsetX();
	int characterY = 0;
	int startingCol = characterX / lv_tileW;
	int tileOffsetX = characterX % lv_tileW;
	//-------------------------------- 
	drawBackground();
	for(int i=0; i<lv_mapH; ++i){
		lv_dstRect->x = 0 - (startingCol * lv_tileW + tileOffsetX);
		lv_dstRect->y = i*lv_dstRect->h;
		for(int j=0; j<lv_mapW; ++j){
			lv_dstRect->x = j*lv_dstRect->w - (startingCol * lv_tileW + tileOffsetX);
			//std::cout<<i<<" "<<j<<" "<<map[i][j]<<std::endl; //remove
			for(unsigned int layer=0; layer<lv_layers.size(); ++layer){
				int tileID = lv_overallTileLayer[i][j][layer];
				if(setSrcRectFromTileID(tileID)){
					//std::cout<<"level.cpp: "<<lv_mapH<<" "<<lv_mapW<<" "<<lv_srcRect->x<<" "<<lv_srcRect->y<<" "<<lv_srcRect->w<<" "<<lv_srcRect->h<<" "<<lv_dstRect->x<<" "<<lv_dstRect->y<<" "<<lv_dstRect->w<<" "<<lv_dstRect->h<<"\n";//remove
					SDL_RenderCopy(lv_mainRendererPointer, lv_texture, lv_srcRect, lv_dstRect);
				}else{
					//empty tile, nothing to render
					//std::cout<<"huh"<<std::endl;//remove
				}
			}
		}
	}
}


bool Level::isComplete() const{
	return lv_complete;
}
