#include "rapidxml.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "spritemanager.h"
//#include "layer.h"
//#include "imagelayer.h"
//#include "tileset.h"



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
		static void TileMap(const char*, std::vector<Layer*>&, std::vector<ImageLayer*>&, std::vector<TileSet*>&, SDL_Renderer*, SDL_Window*);
	private:
		static void insertplayer(rapidxml::xml_node<>*, SpriteManager*, SDL_Renderer*);
		static void insertenemy(rapidxml::xml_node<>*, SpriteManager*);
		static void insertnpc(rapidxml::xml_node<>*, SpriteManager*);
		void parsetotilesets(rapidxml::xml_node<>*, std::vector<TileSet*>&, SDL_Renderer*);
		void parsetoimagelayers(rapidxml::xml_node<>*, std::vector<ImageLayer*>&, SDL_Renderer*, SDL_Window*);
		void parsetolayers(rapidxml::xml_node<>*, std::vector<Layer*>&);
	private:
		static int stringtoint(const char*);
		static int stringtomatrix(const char*, int, int);
		static void commatospace(std::string&);
};
#endif
