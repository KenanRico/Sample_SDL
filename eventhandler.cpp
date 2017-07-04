#include <SDL2/SDL.h>
#include "eventhandler.h"
#include "keyboardhandler.h"
//#include "mousehandler.h"

#include <iostream>


EventHandler::EventHandler() : quitgame(false){
	;
}

EventHandler::~EventHandler(){
	;
}

void EventHandler::parseEvent(SDL_Event& event){
	resetEscape();
	if(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
                quitgame = true;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE: keyboard[KeyboardHandler::ESCAPE] = true; break;
					case SDLK_LCTRL: keyboard[KeyboardHandler::CTRL] = true; break;
					case SDLK_a: keyboard[KeyboardHandler::A] = true; break;
					case SDLK_s: keyboard[KeyboardHandler::S] = true; break;
					case SDLK_d: keyboard[KeyboardHandler::D] = true; break;
					case SDLK_w: keyboard[KeyboardHandler::W] = true; break;
					case SDLK_j: keyboard[KeyboardHandler::J] = true; break;
					case SDLK_k: keyboard[KeyboardHandler::K] = true; break;
					case SDLK_l: keyboard[KeyboardHandler::L] = true; break;
					default: /*other keys to be implemented in the future*/ break;
				}
				break;
			case SDL_KEYUP:
					switch(event.key.keysym.sym){
					case SDLK_ESCAPE: keyboard[KeyboardHandler::ESCAPE] = false; break;
					case SDLK_LCTRL: keyboard[KeyboardHandler::CTRL] = false; break;
					case SDLK_a: keyboard[KeyboardHandler::A] = false; break;
					case SDLK_s: keyboard[KeyboardHandler::S] = false; break;
					case SDLK_d: keyboard[KeyboardHandler::D] = false; break;
					case SDLK_w: keyboard[KeyboardHandler::W] = false; break;
					case SDLK_j: keyboard[KeyboardHandler::J] = false; break;
					case SDLK_k: keyboard[KeyboardHandler::K] = false; break;
					case SDLK_l: keyboard[KeyboardHandler::L] = false; break;
					default: /*every KEYUP correspond to a KEYDOWN*/ break;
				}
				break;
			default: /*other actions to be implemented in the future*/ break;
		}
	}else{
		//When there is no recognized event at this instant
	}
}

void EventHandler::resetEscape(){
	keyboard[KeyboardHandler::ESCAPE] = false;
}

bool EventHandler::quit() const{
	return quitgame;
}

bool EventHandler::getKeyboard(int i) const{
	return keyboard[i];
}



