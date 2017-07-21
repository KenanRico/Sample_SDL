#include "rapidxml.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "spritemanager.h"
#include "levelmanager.h"
#include "tilelayer.h"
#include "imagelayer.h"
#include "tileset.h"



#ifndef XML_PARSER_H
#define XML_PARSER_H
class XMLParser{
	private:
		XMLParser();
		~XMLParser();
		XMLParser(const XMLParser&) = delete;
		XMLParser& operator=(const XMLParser&) = delete;
	public:
		static void Sprite(const char*, SpriteManager*, SDL_Renderer*);
		static void MenuItem();
		static void Levels(const char*, SDL_Renderer*, SDL_Window*, LevelManager&);
		static void TileMap(const char*, const char*, std::vector<TileLayer*>&, std::vector<ImageLayer*>&, std::vector<TileSet*>&, int&, int&, int&, int&, SDL_Renderer*, SDL_Window*);
	private:
		static void insertplayer(rapidxml::xml_node<>*, SpriteManager*, SDL_Renderer*);
		static void insertenemy(rapidxml::xml_node<>*, SpriteManager*);
		static void insertnpc(rapidxml::xml_node<>*, SpriteManager*);
		static void parsetotilesets(rapidxml::xml_node<>*, const char*, std::vector<TileSet*>&, SDL_Renderer*);
		static void parsetoimagelayers(rapidxml::xml_node<>*, const char*, std::vector<ImageLayer*>&, SDL_Renderer*, SDL_Window*);
		static void parsetotilelayers(rapidxml::xml_node<>*, std::vector<TileLayer*>&);
	private:
		static int stringtoint(const char*);
		static int** stringtomatrix(const char*, int, int);
		static void commatospace(std::string&);
};
#endif
