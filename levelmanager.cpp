#include "levelmanager.h"
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

void LevelManager::insert(const char* tmxFile){
	levels.push_back(new Level(tmxFile));
}

const Level& LevelManager::operator[](int){
	return *levels[int];
}

unsigned int LevelManager::totalLevels(){
	return levels.size();
}
