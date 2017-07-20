#include <rapidxml.hpp>
#include <SDL2/SDL.h>
#include "xmlparser.h"
#include "sprite.h"
#include "sprite_player.h"
#include "spritemanager.h"
//#include "layer.h"
//#include "imagelayer.h"
//#include "tileset.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <algorithm>
#include "gamesystem.h"



XMLParser::XMLParser(){;}
XMLParser::~XMLParser(){;}










void XMLParser::Sprite(const char* xml_source, SpriteManager* g_objects, SDL_Renderer* g_renderer){
	std::fstream fs(xml_source);
	std::vector<char> buffer((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	rapidxml::xml_document<> doc;
	doc.parse<0>(&buffer[0]);

	rapidxml::xml_node<>* root = doc.first_node();
	for(rapidxml::xml_node<>* sprite=root->first_node(); sprite!=(rapidxml::xml_node<>*)0; sprite=sprite->next_sibling()){
		std::string type(sprite->name());
		if(type=="Players"){
			for(rapidxml::xml_node<>* player=sprite->first_node(); player!=(rapidxml::xml_node<>*)0; player=player->next_sibling()){
				insertplayer(player, g_objects, g_renderer);
			}

		}else if(type=="Enemies"){
			//enemies not yet implemented


		}else if(type=="NPCs"){
			//NPCs not yet implemented

		}

	}


}

void XMLParser::insertplayer(rapidxml::xml_node<>* player, SpriteManager* g_objects, SDL_Renderer* g_renderer){
	std::string name(player->first_attribute("name")->value());
	std::string source(player->first_attribute("source")->value());
	int sourceX = stringtoint(player->first_attribute("sourceX")->value());
	int sourceY = stringtoint(player->first_attribute("sourceY")->value());
	int spriteW = stringtoint(player->first_attribute("spriteW")->value());
	int spriteH = stringtoint(player->first_attribute("spriteH")->value());
	int displayX = stringtoint(player->first_attribute("displayX")->value());
	int displayY = stringtoint(player->first_attribute("displayY")->value());
	int agility = stringtoint(player->first_attribute("agility")->value());
	int strength = stringtoint(player->first_attribute("strength")->value());
	int intelligence = stringtoint(player->first_attribute("intelligence")->value());
	int dexterity = stringtoint(player->first_attribute("dexterity")->value());
	g_objects->insert(name.c_str(), new Player(g_renderer, source.c_str(), sourceX, sourceY, spriteW, spriteH, displayX, displayY, spriteW, spriteH, agility, strength, intelligence, dexterity));

}










void XMLParser::MenuItem(){


}
















void XMLParser::TileMap(const char* tmx_source, std::vector<Layer*>& layers, std::vector<ImageLayer*>& imagelayers, std::vector<TileSet*>& tilesets, SDL_Renderer* mainRendererPointer, SDL_Window* mainWindowPointer){
	std::fstream fs(tmx_source);
	std::vector<char> buffer((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	rapidxml::xml_document<> doc;
	doc.parse<0>(&buffer[0]);

	rapidxml::xml_node<>* root = doc.first_node();
	for(rapidxml::xml_node<>* element = root->first_node(); element!=(rapidxml::xml_node<>*)0; element=element->next_sibling()){
		std::string element(element->name());
		if(element=="tileset"){
			parsetotilesets(element, tilesets, mainRendererPointer);
		}else if(element=="imagelayer"){
			parsetoimagerlayers(element, imagerlayers, mainRendererPointer, mainWindowPointer);
		}else if(element=="layers"){
			parsetolayers(element, layers);
		}else{
			//other potential elements
		}
	}
}

void XMLParser::parsetotilesets(rapidxml::node<>* element, std::vector<TileSet*>& tilesets, SDL_Renderer* mainRendererPointer){
	rapidxml::xml_node<>* image = element->first_node("image");
	std::string name(element->first_attribute("name")->value());
	std::string source(image->first_attribute("source")->value());
	int firstgid = stringtoint(element->first_attribute("firstgid")->value());
	int tilewidth = stringtoint(element->first_attribute("tilewidth")->value());
	int tileheight = stringtoint(element->first_attribute("tileheight")->value());
	int tilecount = stringtoint(element->first_attribute("tilecount")->value());
	int columns = stringtoint(element->first_attribute("columns")->value());
	tilesets.push_back(new TileSet(mainRendererPointer, name.c_str(), source.c_str(), firstgid, tilewidth, tileheight, tilecount, columns));
}
void XMLParser::parsetoimagelayers(rapidxml::node<>* element, std::vector<ImageLayer*>& imagelayers, SDL_Renderer* mainRendererPointer, SDL_Window* mainWindowPointer){
	rapidxml::xml_node<>* image = element->first_node("image");
	std::string name(element->first_attribute("name")->value());
	std::string source(image->first_attribute("source")->value());
	int width = stringtoint(image->first_attribute("width")->value());
	int height = stringtoint(image->first_attribute("height")->value());
	int offsetx = stringtoint(element->first_attribute("offsetx")->value());
	int offsety = stringtoint(element->first_attribute("offsety")->value());
	imagelayers.push_back(new ImageLayer(name.c_str(), source.c_str(), width, height, offsetx, offsety, mainRendererPointer, mainWindowPointer));`
}
void XMLParser::parsetolayers(rapidxml::node<>* element, std::vector<Layer*>& layers){
	int columns = stringtoint(element->first_attribute("width")->value());
	int rows = stringtoint(element->first_attribute("height")->value());
	std::string datastring(element->first_node("data")->value());
	int** data = stringtomatrix(datastring.c_str(), columns, rows);
	layers.push_back(new Layer(data, columns, rows));
}



int XMLParser::stringtoint(const char* sValue){
	int iValue = 0;
	std::string s(sValue);
	int digit = 0;
	try{
		for(std::string::iterator i=s.end()-1; i>=s.begin(); --i){
			int curr = *i-48;
			iValue += (curr>=0&&curr<=9)?curr*powf(10,digit):0;
			if(*i=='-'){
				iValue *= 0;
				throw "Error in XMLParser::stringtoint";
			}else;
			++digit;
		}
	}catch(const char* Err){
		GameSystem::writeErrorMessage(Err);
	}
	return iValue;
}

int XMLParser::stringtomatrix(const char* datastring, int cols, int rows){
	std::stringstream ss(datastring);
	std::string line("");
	int** data = new int*[rows]();
	for(int i=0; i<rows; ++i){
		data[i] = new int[cols]();
	}
	int rownumber = 0;
	int colnumber = 0;
	getline(ss,line);
	while(getline(ss, line)){
		commatospace(line);
		std::stringstream currentline_ss(line);
		while(currentline_ss >> data[rownumber][colnumber++]);
		++rownumber;
		colnumber = 0;
	}
	return data;
}
void XMLParser::commatospace(std::string& line){
	std::replace(line.begin(), line.end(), ',', ' ');
}
