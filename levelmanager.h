#include <SDL2/SDL.h>
#include <vector>
#include "level.h"


#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H
class LevelManager{
	private:
		std::vector<Level*> levels;
	public:
		LevelManager();
		~LevelManager();
		LevelManager(const LevelManager&) = delete;
		LevelManager& operator=(const LevelManager&) = delete;
	public:
		void insert(const char*, SDL_Renderer*, SDL_Window*); //taking .tmx files to convert to Level objects
		const Level& operator[](int);
		unsigned int totalLevels();
};
#endif
