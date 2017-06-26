#include <SDL2/SDL.h>

#ifndef GAME_H
#define GAME_H
class Game{
	private:
		enum class State;
	private:
		SDL_Window* g_window;
		int g_width;
		int g_height;
		SDL_Renderer* g_renderer;
		State g_state;
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
		void handleEvents();
		void updateGame();
		void renderGame();
};
#endif
