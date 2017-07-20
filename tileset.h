#include <SDL2/SDL.h>
#include <string>


#ifndef TILESET_H
#define TILESET_H
class TileSet{
	private:
		SDL_Texture* texture;
		std::string name;
		std::string source;
		int firstgid;
		int lastgid;
		int tilewidth;
		int tileheight;
		int tilecount;
		int columns;
		int rows;
	public:
		TileSet() = delete;
		~TileSet();
		TileSet(const TileSet&) = delete;
		TileSet& operator=(const TileSet&) = delete;
	public:
		TileSet(SDL_Renderer*, const char*, const char*, int, int, int, int, int); //no lastgid or rows initialization
	public:
		int getFirstTileID() const;
		int getLastTileID() const;
		int getTexture() const;

};
#endif
