#include <SDL2/SDL.h>
#include "gamesystem.h"
#include "game.h"
#include <iostream>

#ifdef main
#undef main
#endif

void testRun();

int main()
{
	Game::startGame();
//	testRun();
	return 0;
}



void testRun(){
	GameSystem::Init();

	SDL_Window* window = SDL_CreateWindow("This is a window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,640, 480, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = (SDL_Renderer*)0;
	if(window!=(SDL_Window*)0){
		renderer = SDL_CreateRenderer(window,-1, 0);
		SDL_Surface* surface = SDL_LoadBMP("assets/Geoff.bmp");
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		SDL_Rect rectangle_src;
		SDL_Rect rectangle_dst;
		SDL_QueryTexture(texture, NULL, NULL, &rectangle_src.w, &rectangle_src.h);
		rectangle_src.x = 0;
		rectangle_src.y = 0;
		rectangle_dst.x = rectangle_src.x;
		rectangle_dst.y = rectangle_src.y;
		rectangle_dst.w = rectangle_src.w;
		rectangle_dst.h = rectangle_src.h;
		std::cout<<rectangle_src.x<<" "<<rectangle_src.y<<" "<<rectangle_src.w<<" "<<rectangle_src.h<<std::endl;
		SDL_SetRenderDrawColor(renderer,100,0,0,255);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, &rectangle_src, &rectangle_dst);
		SDL_RenderPresent(renderer);
		SDL_Delay(5000);
	}else;
	GameSystem::writeMessage("Hi");
	std::cout<<(SDL_INIT_AUDIO|SDL_INIT_VIDEO)<<std::endl;
	GameSystem::Quit();
}
