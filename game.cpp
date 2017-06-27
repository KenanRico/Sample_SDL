#include "game.h"
#include "gamesystem.h"
#include <SDL2/SDL.h>
#include "sprite.h"
#include <iostream>

enum class Game::State{
	RUN,
	STOP,
	PAUSE
};


Game::Game(): 
g_window((SDL_Window*)0), 
g_windowW(640), 
g_windowH(480), 
g_renderer((SDL_Renderer*)0), 
g_state(State::STOP), 
g_testSprite(g_renderer, "assets/Geoff.bmp"){
	initSystems();
}
Game::~Game(){
	deinitSystems();
}


void Game::initSystems(){
	GameSystem::Init();
	g_window = SDL_CreateWindow("This is a window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, g_windowW, g_windowH, SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
	if(g_window!=(SDL_Window*)0){
		g_renderer = SDL_CreateRenderer(g_window,-1, 0);
		if(g_renderer!=(SDL_Renderer*)0){
			g_testSprite.createSprite();
		}
		SDL_SetRenderDrawColor(g_renderer,100,0,0,0);
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
		if(g_state==State::RUN){
			handleEvents_RUN();
			updateGame();
			renderGame();
		}else if(g_state==State::PAUSE){
			showPauseMenu();
			while(g_state==State::PAUSE){
				handleEvents_PAUSE();
			}
			hidePauseMenu();
			//other PAUSE operations
		}else{
			//More states in the future?
		}
	}

}
void Game::handleEvents_RUN(){
	SDL_Event event;
	if(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				g_state = State::STOP;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						g_state = State::PAUSE;
						GameSystem::writeMessage("game paused");
						break;
					case SDLK_RIGHT:
						g_testSprite.moveRight();
					default:
						//Keys outside of consideration
						break; 
				}
				break;
			default:
				//Events outside of consideration
				break;
		}
	}else{
		//When there is no recognized event at this instant
	}

}
void Game::updateGame(){


}
void Game::renderGame(){
	SDL_RenderClear(g_renderer);
	SDL_RenderCopy(g_renderer, g_testSprite.getTexturePtr(), g_testSprite.getSourceRectanglePtr(), g_testSprite.getDestinationRectPtr());
	SDL_RenderPresent(g_renderer);


}

void Game::showPauseMenu(){


}

void Game::hidePauseMenu(){


}

void Game::handleEvents_PAUSE(){
	SDL_Event event;
	if(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				g_state = State::STOP;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						g_state = State::RUN;
						GameSystem::writeMessage("game resumed");
						break;
					default:
						//...
						break;
				}
				break;
			default:
				//...
				break;
		}
	}else{
		//no recognized events
	}
}
