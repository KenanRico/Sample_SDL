#include <SDL2/SDL.h>
//#include "layer.h"
//#include "tileset.h"
//#include "imagelayer.h"
#include <string>
#include <vector>


#ifndef LEVEL_H
#define LEVEL_H
class Level{
	private:
		std::string lv_name;
		std::vector<TileLayer*> lv_layers;
		std::vector<ImageLayer*> lv_imagelayers;
		std::vector<TileSet*> lv_tilesets;
		int lv_mapH;
		int lv_mapW;
		int lv_tileH;
		int lv_tileW;
		bool lv_complete;
		SDL_Renderer* mainRendererPointer;
		SDL_Window* mainWindowPointer;
	public:
		Level() = delete;
		~Level();
		Level(const Level&) = delete;
		Level& operator=(const Level&) = delete;
	public:
		Level(const char*, SDL_Renderer*, SDL_Window*);
	private:
		bool initLevel(); //Parse lv_name and insert TileLayer objects and TileSet objects
		void destroyLevel(); //Free layer and tileset objects
	private:
		void drawBackground();
		int** overallTileLayer();
		SDL_Texture* getTextureFromTileID(int);
	public:
		void updateLevel();
		void renderLevel();
		bool isComplete();
};
#endif
