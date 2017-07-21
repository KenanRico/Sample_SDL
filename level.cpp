#include "level.h"
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <sstream>
#include "tilelayer.h"
#include "tileset.h"
#include "imagelayer.h"
#include "gamesystem.h"
#include "xmlparser.h"

#include <iostream>//remove



Level::Level(const char* tilemap_dir, const char* tilemap_file, SDL_Renderer* g_renderer, SDL_Window* g_window): 
lv_dir(tilemap_dir), lv_file(tilemap_file), 
lv_mapH(0), lv_mapW(0), lv_tileH(0), lv_tileW(0), lv_complete(false), 
mainRendererPointer(g_renderer), texture((SDL_Texture*)0), mainWindowPointer(g_window), 
lv_srcRect(new SDL_Rect({0,0,0,0})), lv_dstRect(new SDL_Rect({0,0,0,0})){
	initLevel();
}
Level::~Level(){
	destroyLevel();
}


void Level::initLevel(){
	XMLParser::TileMap(lv_dir.c_str(), lv_file.c_str(), lv_layers, lv_imagelayers, lv_tilesets, lv_mapH, lv_mapW, lv_tileH, lv_tileW, mainRendererPointer, mainWindowPointer);
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
	delete lv_srcRect;
	delete lv_dstRect;
}


int** Level::overallTileLayer() const{
	//allocate array[mapH][mahW] to all 0s
	int** finalLayer = new int*[lv_mapH]();
	for(int i=0; i<lv_mapH; ++i){
		finalLayer[i] = new int[lv_mapW]();
	}
	//from upper layer to lower layer, put non-zero values in
	for(std::vector<TileLayer*>::const_iterator iter=lv_layers.begin(); iter<lv_layers.end(); ++iter){
		int rows = (*iter)->getTileLayerH();
		int cols = (*iter)->getTileLayerW();
		for(int i=0; i<rows; ++i){
			for(int j=0; j<cols; ++j){
				int tileID = (*iter)->getTileID(i,j);
				if(tileID!=0){
					finalLayer[i][j] = (*iter)->getTileID(i,j);
				}else;
			}
		}
	}
//	for(int i=0; i<lv_mapH; ++i){
//		for(int j=0; j<lv_mapW; ++j){
//			std::cout<<finalLayer[i][j]<<" ";
//		}
//		std::cout<<"\n";
//	}
	return finalLayer;
}

bool Level::setTextureFromTileID(int tileID) const{
	//return a texture from given tile ID
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
				texture = (*i)->getTexture();
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
	SDL_GetWindowSize(mainWindowPointer, &windowW, &windowH);
	lv_dstRect->h = windowH/lv_mapH;
	lv_dstRect->w = windowW/lv_mapW;
	for(std::vector<ImageLayer*>::const_iterator iter=lv_imagelayers.end()-1; iter>=lv_imagelayers.begin(); --iter){
		(*iter)->updateImageLayer(windowW, windowH);
	}
}
void Level::renderLevel() const{
	int** map = overallTileLayer(); //final array(mapH*mapW) of data encoding of all tile layers combined
	drawBackground();
	for(int i=0; i<lv_mapH; ++i){
		lv_dstRect->x = 0;
		lv_dstRect->y = i*lv_dstRect->h;
		for(int j=0; j<lv_mapW; ++j){
			lv_dstRect->x = j*lv_dstRect->w;
			//std::cout<<i<<" "<<j<<" "<<map[i][j]<<std::endl; //remove
			int tileID = map[i][j];
			if(setTextureFromTileID(tileID)){
				//std::cout<<"level.cpp: "<<lv_mapH<<" "<<lv_mapW<<" "<<lv_srcRect->x<<" "<<lv_srcRect->y<<" "<<lv_srcRect->w<<" "<<lv_srcRect->h<<" "<<lv_dstRect->x<<" "<<lv_dstRect->y<<" "<<lv_dstRect->w<<" "<<lv_dstRect->h<<"\n";//remove
				SDL_RenderCopy(mainRendererPointer, texture, lv_srcRect, lv_dstRect);
			}else{
				//empty tile, nothing to render
				//std::cout<<"huh"<<std::endl;//remove
			}
		}
	}
	for(int i=0; i<lv_mapH; ++i){
		delete[] map[i];
	}
	delete[] map;
}


bool Level::isComplete() const{
	return lv_complete;
}
