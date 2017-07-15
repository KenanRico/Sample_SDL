//#include "layer.h"
//#include "tileset.h"



#ifndef LEVEL_H
#define LEVEL_H
class Level{
	private:
		std::string l_name;
		std::vector<Layer*> l_layers;
		std::vector<TileSet*> l_tilesets;
		bool l_complete;
		SDL_Renderer* mainRendererPointer;
		SDL_Window* mainWindowPointer;
	public:
		Level() = delete;
		~Level();
		Level(const Level&) = delete;
		Level& operator=(const Level&) = delete;
	public:
		Level(const char*);
	private:
		bool initLevel(); //Parse l_name and insert Layer objects and TileSet objects
	public:
		void updateLevel();
		void renderLevel();
		bool isComplete();
};
#endif
