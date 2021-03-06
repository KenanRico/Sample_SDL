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
		int columnCount() const;
	public:
		inline int getTileH() const{
			return tileheight;
		}
		inline int getTileW() const{
			return tilewidth;
		}
		inline int getFirstTileID() const{
			return firstgid;
		}
		inline int getLastTileID() const{
			return lastgid;
		}
		inline SDL_Texture* getTexture() const{
			return texture;
		}

};
#endif
