#include <SDL2/SDL.h>
#include "game.h"
#include "gamesystem.h"
#include "spritemanager.h"
#include "sprite.h"
#include "sprite_player.h"
#include "eventhandler.h"
#include "keyboardhandler.h"
//#include "mousehandler.h"
#include "menuitem.h"
#include "menu_button.h"
#include "menu.h"
#include "xmlparser.h"




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

struct Game::LevelInfo{
	//LevelManager levels;//level_recover
	int count = 0;
};


Game::Game(): 
g_window((SDL_Window*)0), 
g_renderer((SDL_Renderer*)0), 
g_state(State::NONE), 
g_objects((SpriteManager*)0){
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
			g_objects = SpriteManager::Init();
			if(g_objects!=(SpriteManager*)0){
				loadAllObjects();
				createLevels();
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
	XMLParser::Sprite("items/sprites.xml", g_objects, g_renderer);
}
void Game::createLevels(){
	/*g_levels.levels.insert("levels/level_1", g_renderer, g_window);
	g_levels.levels.insert("levels/level_2", g_renderer, g_window);*///level_recover
}


void Game::run(){
	mainMenu();
	gameLoop();
}

void Game::mainMenu(){
	Menu mainmenu(g_renderer);
	mainmenu.setBackground("assets/mainmenu.png");
	mainmenu.addItem("start", new Button(g_renderer, "assets/button_blue.png", 0,0,140,40, 400,280,150,45));
	mainmenu.addItem("exit", new Button(g_renderer, "assets/button_red.png", 0,0,140,40, 400,360,150,45));
	mainmenu.renderMenu(g_window);
	const MenuItem& start = mainmenu["start"];
	const MenuItem& exit = mainmenu["exit"];
	while(g_state!=State::RUN && g_state!=State::STOP){
		int starttime = SDL_GetTicks();
		handleEvents();
		mainmenu.updateMenu(g_event);
		mainmenu.renderMenu(g_window);
		if(start.triggered()){
			g_state = State::RUN;
			GameSystem::writeMessage("Starting game");
		}else if(exit.triggered()){
			g_state = State::STOP;
			GameSystem::writeMessage("Exiting game");
		}else;
		int timespent = SDL_GetTicks()-starttime;
		if(timespent<GameSystem::FrameTime){
			SDL_Delay((int)(GameSystem::FrameTime-timespent));
		}else;
	}
}
void Game::pauseMenu(){
	Menu pausemenu(g_renderer);
	pausemenu.setBackground("assets/mainmenu.png");
	pausemenu.addItem("resume", new Button(g_renderer, "assets/button_yellow.png", 0,0,140,40, 300,280,150,45));
	pausemenu.addItem("exit", new Button(g_renderer, "assets/button_red.png", 0,0,140,40, 300,360,150,45));
	pausemenu.renderMenu(g_window);
	const MenuItem& resume = pausemenu["resume"];
	const MenuItem& exit = pausemenu["exit"];
	while(g_state!=State::RUN && g_state!=State::STOP){
		int starttime = SDL_GetTicks();
		handleEvents();
		pausemenu.updateMenu(g_event);
		pausemenu.renderMenu(g_window);
		if(resume.triggered()){
			g_state = State::RUN;
			GameSystem::writeMessage("Resuming game");
		}else if(exit.triggered()){
			g_state = State::STOP;
			GameSystem::writeMessage("Exiting game");
		}else;
		int timespent = SDL_GetTicks()-starttime;
		if(timespent<GameSystem::FrameTime){
			SDL_Delay((int)(GameSystem::FrameTime-timespent));
		}else;
	}
}


void Game::gameLoop(){
	//while(g_levels.count<g_levels.levels.totalLevels()){//level_recover
		while(g_state!=State::STOP && g_state!=State::NONE /*&& !g_levels.levels[g_level.count].iscomplete()*//*level_recover*/){
			if(g_state==State::RUN){
				int starttime = SDL_GetTicks();
				handleEvents();
				updateGame();
				renderGame();
				int timespent = SDL_GetTicks()-starttime;
				if(timespent<GameSystem::FrameTime){
					SDL_Delay((int)(GameSystem::FrameTime-timespent));
				}else;
			}else if(g_state==State::PAUSE){
				pauseMenu();
				//other PAUSE operations
			}else{
				//More states in the future?
			}
		}
		if(g_state==State::STOP || g_state==State::NONE){
			//break;//level_recover
		}/*else if(g_levels.levels[g_level.count].iscomplete()){//level_recover
			++g_levels.count;
		}*/else{
			GameSystem::writeErrorMessage("Huh!? Gameloop broken unexpectedly");
		}
		/*if(g_levels.count==g_levels.levels.totalLevels()-1){
			g_state = State::STOP;
		}else;*///level_recover
	//}//level_recover
}
void Game::handleEvents(){
	g_event.parseEvent();
	if(g_event.quit()){
		g_state = State::STOP;
	}else;
	if(g_state==State::RUN){
		if(g_event.getKeyboard()[KeyboardHandler::ESCAPE]){
			g_state = State::PAUSE;
			GameSystem::writeMessage("game paused");
		}else;
	}else if(g_state==State::PAUSE){
		if(g_event.getKeyboard()[KeyboardHandler::ESCAPE]){
			g_state = State::RUN;
			GameSystem::writeMessage("game resumed");
		}else;
	}
}



void Game::updateGame(){
	//Note: This function is responsible for updating everything that indirectly responds to or that is independent from user inputs
	/*g_levels.levels[g_levels.count].updateLevel();*///level_recover
	g_objects->updateAllStates(g_event);
	g_objects->updateAllSprites();
}
void Game::renderGame(){
	SDL_RenderClear(g_renderer);
	/*g_levels.levels[g_levels.count].renderLevel();*///lever_recover
	g_objects->renderAllSprites();

	SDL_RenderPresent(g_renderer);
}

void Game::showPauseMenu(){


}

void Game::hidePauseMenu(){


}

