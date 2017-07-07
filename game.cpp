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
	NONE,
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
	g_objects->insert("lucas", new Player(g_renderer, "assets/lucas.png", 0,0,37,50,10,10,37,50, 9,9,9,9));	
}


void Game::run(){
	g_state = State::RUN; //remove after implementing main menu
//	mainMenu();
	gameLoop();
}

/*void Game::mainMenu(){
	Menu mainmenu;
	mainmenu.setBackground(g_renderer, "assets/background/mainmenu.png", 0,0,1920,1280, 0,0, g_window->width, g_window->height);
	mainmenu.addItem("start", new Button(g_renderer, "start", x,y,w,h, x,y,w,h));
	mainmenu.addItem("exit", new Button(g_renderer, "quit", x,y,w,h, x,y,w,h));
	mainmenu.display();
	MenuItem& start = mainmenu["start"];
	MenuItem& exit = mainmenu["exit"];
	while(g_state!=State::RUN && g_state!=State::STOP){
		g_event.parseEvent();
		mainmenu.update(g_event);
		if(start.triggered()){
			g_state = State::RUN;
		}else if(exit.triggered()){
			g_state = State::STOP;
		}else;
	}
}*/

void Game::gameLoop(){
	while(g_state!=State::STOP && g_state!=State::NONE){
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
	g_event.parseEvent();
	if(g_event.quit()){
		g_state = State::STOP;
	}else;
	if(g_event.getKeyboard()[KeyboardHandler::ESCAPE]){
		g_state = State::PAUSE;
		GameSystem::writeMessage("game paused");
	}else;
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
	g_event.parseEvent();
	if(g_event.quit()){
		g_state = State::STOP;
	}else;
	if(false/*on resume button clicked*/){
		g_state = State::RUN;
		GameSystem::writeMessage("game resumed");
		
	}else;
}
