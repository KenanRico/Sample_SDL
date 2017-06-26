#include <SDL2/SDL.h>
#include "gamesystem.h"
#include "game.h"
#include <iostream>

#ifdef main
#undef main
#endif

void gameRun();

int main()
{
	Game g;
	g.run();
	return 0;
}

void gameRun(){
	GameSystem::Init();

	SDL_Window* window = SDL_CreateWindow("This is a window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,640, 480, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = (SDL_Renderer*)0;
	if(window!=(SDL_Window*)0){
		renderer = SDL_CreateRenderer(window,-1, 0);
		SDL_SetRenderDrawColor(renderer,100,0,0,255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(5000);
	}else;
	GameSystem::writeMessage("Hi");
	std::cout<<(SDL_INIT_AUDIO|SDL_INIT_VIDEO)<<std::endl;
	GameSystem::Quit();
}
