#include <SDL2/SDL.h>
#include "sprite.h"

#ifndef GAME_H
#define GAME_H
class Game{
	private:
		enum class State;
	private:
		SDL_Window* g_window;
		int g_windowW;
		int g_windowH;
		SDL_Renderer* g_renderer;
		State g_state;
		Sprite g_testSprite;
	public:
		Game();
		~Game();
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
	public:
		void run();
	private:
		void initSystems();
		void deinitSystems();

		void gameLoop();
		void handleEvents_RUN();
		void updateGame();
		void renderGame();

		void showPauseMenu();
		void hidePauseMenu();
		void handleEvents_PAUSE();
};
#endif
