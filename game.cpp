#include <SDL2/SDL.h>
#include "game.h"
#include "gamesystem.h"
#include "objectmanager.h"
#include "sprite.h"
#include "sprite_player.h"
#include "eventhandler.h"
#include "keyboardhandler.h"
//#include "mousehandler.h"

bool Game::Running = false;

void Game::startGame(){
	if(!Game::Running){
		Game::Running = true;
		Game game;
		game.run();
	}else{
		GameSystem::writeErrorMessage("The game is already running!");
	}
}


enum class Game::State{
	RUN,
	STOP,
	PAUSE
};


Game::Game(): 
g_window((SDL_Window*)0), 
g_renderer((SDL_Renderer*)0), 
g_state(State::STOP), 
g_objects((ObjectManager*)0){
	initSystems();
}
Game::~Game(){
	deinitSystems();
}


void Game::initSystems(){
	GameSystem::Init();
	g_window = SDL_CreateWindow("This is a window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
	if(g_window!=(SDL_Window*)0){
		g_renderer = SDL_CreateRenderer(g_window,-1, 0);
		if(g_renderer!=(SDL_Renderer*)0){
			g_objects = ObjectManager::Init();
			if(g_objects!=(ObjectManager*)0){
				loadAllObjects();
			}else{
				GameSystem::writeErrorMessage("Failed to init g_objects");
			}
		}else{
			GameSystem::writeErrorMessage("Failed to initialize g_renderer");
		}
		SDL_SetRenderDrawColor(g_renderer,100,0,100,255);
		SDL_RenderClear(g_renderer);
		SDL_RenderPresent(g_renderer);
	}else;
	GameSystem::writeMessage("Inited system");
}

void Game::deinitSystems(){
	SDL_DestroyWindow(g_window);
	SDL_DestroyRenderer(g_renderer);
	GameSystem::Quit();
	delete g_objects;
	if(g_state==State::STOP){
		GameSystem::writeMessage("De-Inited system");
	}else{
		GameSystem::writeErrorMessage("Game has stopped unexpectedly");
	}
}

void Game::loadAllObjects(){
	//load every sprite used in the game
	//Or we can load the ones that are rendered right off the bat and gradually load more as they come in
	//g_objects->insert("lucas", new Sprite(g_renderer, "assets/lucas.png", 3,50,37,50,10,10,30,50));	
	g_objects->insert("lucas", new Player(g_renderer, "assets/lucas.png", 3,50,37,50,10,10,30,50, 9,9,9,9));	
}


void Game::run(){
	g_state = State::RUN;
	gameLoop();

}
void Game::gameLoop(){
	while(g_state!=State::STOP){
		if(g_state==State::RUN){
			int starttime = SDL_GetTicks();
			handleEvents_RUN();
			updateGame();
			renderGame();
			int timespent = SDL_GetTicks()-starttime;
			if(timespent<GameSystem::FrameTime){
				SDL_Delay((int)(GameSystem::FrameTime-timespent));
			}else;
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
	g_event.parseEvent(event);
	if(g_event.quit()){
		g_state = State::STOP;
	}else;
	if(g_event.getKeyboard(KeyboardHandler::ESCAPE)){
		g_state = State::PAUSE;
		GameSystem::writeMessage("game paused");
	}else;



	/*if(SDL_PollEvent(&event)){
		Sprite* character = g_objects->get("lucas");
		character->setAction(&event);
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
						break;
					case SDLK_LEFT:
						break;
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
	}*/

}
void Game::updateGame(){
	//Note: This function is responsible for updating everything that indirectly responds to or that is independent from user inputs
	g_objects->get("lucas")->updateState(g_event);
	g_objects->get("lucas")->updateSprite();
}
void Game::renderGame(){
	SDL_RenderClear(g_renderer);
	g_objects->get("lucas")->renderSprite();


	SDL_RenderPresent(g_renderer);
}

void Game::showPauseMenu(){


}

void Game::hidePauseMenu(){


}

void Game::handleEvents_PAUSE(){
	SDL_Event event;
	g_event.parseEvent(event);
	if(g_event.quit()){
		g_state = State::STOP;
	}else;
	if(false/*on resume button clicked*/){
		g_state = State::RUN;
		GameSystem::writeMessage("game resumed");
		
	}else;
	/*if(SDL_PollEvent(&event)){
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
	}*/
}
