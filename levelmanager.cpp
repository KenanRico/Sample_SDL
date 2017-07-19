#include "levelmanager.h"
#include <SDL2/SDL.h>
#include "level.h"
#include <vector>



LevelManager::LevelManager(){
	;
}

LevelManager::~LevelManager(){
	for(std::vector<Level*>::iterator i=levels.begin(); i<levels.end(); ++i){
		delete *i;
	}
}

void LevelManager::insert(const char* tmxFile, SDL_Renderer* g_renderer, SDL_Window* g_window){
	levels.push_back(new Level(tmxFile, g_renderer, g_window));
}

const Level& LevelManager::operator[](int){
	return *levels[int];
}

unsigned int LevelManager::totalLevels(){
	return levels.size();
}
