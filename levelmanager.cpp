#include "levelmanager.h"
#include <SDL2/SDL.h>
#include <vector>
#include "level.h"
#include "sprite_player.h"
#include "xmlparser.h"



LevelManager::LevelManager(){
	;
}

LevelManager::~LevelManager(){
	for(std::vector<Level*>::iterator i=levels.begin(); i<levels.end(); ++i){
		delete *i;
	}
}

void LevelManager::insertAll(const char* levelsFile, SDL_Renderer* g_renderer, SDL_Window* g_window, const Player* player){
	XMLParser::Levels(levelsFile, g_renderer, g_window, player, *this);
	//levels.push_back(new Level(levelsFile, g_renderer, g_window));
}
void LevelManager::insertLevel(const char* dir, const char* file, SDL_Renderer* g_renderer, SDL_Window* g_window, const Player* player){
	levels.push_back(new Level(dir, file, g_renderer, g_window, player));
}


const Level& LevelManager::operator[](int index){
	return *levels[index];
}

int LevelManager::totalLevels(){
	return levels.size();
}
