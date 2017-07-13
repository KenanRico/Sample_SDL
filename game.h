#include <SDL2/SDL.h>
#include "spritemanager.h"
#include "eventhandler.h"
#include "keyboardhandler.h"
//#include "mousehandler.h"


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
		SpriteManager* g_objects;
		EventHandler g_event;	
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

		void mainMenu();
		void pauseMenu();
		void gameLoop();
		void handleEvents();
		void updateGame();
		void renderGame();

		void showPauseMenu();
		void hidePauseMenu();
};
#endif
