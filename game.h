#include <SDL2/SDL.h>
#include "sprite.h"
#include "objectmanager.h"

#ifndef GAME_H
#define GAME_H
class Game{

	private: static bool Running;
	public: static void startGame();

	private:
		enum class State;
	private:
		SDL_Window* g_window;
		SDL_Renderer* g_renderer;
		State g_state;
//		Sprite g_testSprite;//Remove after sorting everything out
		ObjectManager* g_objects;	
	private:
		Game();
	public:
		~Game();
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
	public:
		void run();
	private:
		void initSystems();
		void deinitSystems();

		void loadAllObjects();

		void gameLoop();
		void handleEvents_RUN();
		void updateGame();
		void renderGame();

		void showPauseMenu();
		void hidePauseMenu();
		void handleEvents_PAUSE();
};
#endif
