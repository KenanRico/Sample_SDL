#include "game.h"
#include "gamesystem.h"
#include <SDL2/SDL.h>


enum class Game::State{
	RUN,
	STOP
};


Game::Game(): g_window((SDL_Window*)0), g_width(640), g_height(480), g_renderer((SDL_Renderer*)0), g_state(State::STOP){
	initSystems();
}
Game::~Game(){
	deinitSystems();
}


void Game::initSystems(){
	GameSystem::Init();
	g_window = SDL_CreateWindow("This is a window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, g_width, g_height, SDL_WINDOW_OPENGL);
	if(g_window!=(SDL_Window*)0){
		g_renderer = SDL_CreateRenderer(g_window,-1, 0);
		SDL_SetRenderDrawColor(g_renderer,100,0,0,255);
		SDL_RenderClear(g_renderer);
		SDL_RenderPresent(g_renderer);
	}else;
	GameSystem::writeMessage("Inited system");
}

void Game::deinitSystems(){
	SDL_DestroyWindow(g_window);
	SDL_DestroyRenderer(g_renderer);
	GameSystem::Quit();
	if(g_state==State::STOP){
		GameSystem::writeMessage("De-Inited system");
	}else{
		GameSystem::writeErrorMessage("Game has stopped unexpectedly");
	}
}


void Game::run(){
	g_state = State::RUN;
	gameLoop();

}
void Game::gameLoop(){
	while(g_state!=State::STOP){
		handleEvents();
		updateGame();
		renderGame();
	}

}
void Game::handleEvents(){
	SDL_Event event;
	if(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				g_state = State::STOP;
				break;
			default:
				//Events outside of consideration
				break;
		}
	}else{
//		GameSystem::writeMessage("No event");
	}

}
void Game::updateGame(){


}
void Game::renderGame(){



}
