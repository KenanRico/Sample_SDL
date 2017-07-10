#include <SDL2/SDL.h>
#include "eventhandler.h"
#include "keyboardhandler.h"
#include "mousehandler.h"

#include <iostream>


EventHandler::EventHandler() : quitgame(false){
	;
}

EventHandler::~EventHandler(){
	;
}

void EventHandler::parseEvent(){
	resetEscape();
	SDL_Event event;
	if(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
                quitgame = true;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE: keyboard.set(KeyboardHandler::ESCAPE) = true; break;
					case SDLK_LCTRL: keyboard.set(KeyboardHandler::CTRL) = true; break;
					case SDLK_a: keyboard.set(KeyboardHandler::A) = true; break;
					case SDLK_s: keyboard.set(KeyboardHandler::S) = true; break;
					case SDLK_d: keyboard.set(KeyboardHandler::D) = true; break;
					case SDLK_w: keyboard.set(KeyboardHandler::W) = true; break;
					case SDLK_j: keyboard.set(KeyboardHandler::J) = true; break;
					case SDLK_k: keyboard.set(KeyboardHandler::K) = true; break;
					case SDLK_l: keyboard.set(KeyboardHandler::L) = true; break;
					default: /*other keys to be implemented in the future*/ break;
				}
				break;
			case SDL_KEYUP:
					switch(event.key.keysym.sym){
					case SDLK_ESCAPE: keyboard.set(KeyboardHandler::ESCAPE) = false; break;
					case SDLK_LCTRL: keyboard.set(KeyboardHandler::CTRL) = false; break;
					case SDLK_a: keyboard.set(KeyboardHandler::A) = false; break;
					case SDLK_s: keyboard.set(KeyboardHandler::S) = false; break;
					case SDLK_d: keyboard.set(KeyboardHandler::D) = false; break;
					case SDLK_w: keyboard.set(KeyboardHandler::W) = false; break;
					case SDLK_j: keyboard.set(KeyboardHandler::J) = false; break;
					case SDLK_k: keyboard.set(KeyboardHandler::K) = false; break;
					case SDLK_l: keyboard.set(KeyboardHandler::L) = false; break;
					default: /*every KEYUP correspond to a KEYDOWN*/ break;
				}
				break;
			case SDL_MOUSEMOTION:
				mouse.setPosition(event.motion.x, event.motion.y);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse.setClick(event.button.button-1, true);
				mouse.setClickPosition(event.button.x, event.button.y);
				break;
			case SDL_MOUSEBUTTONUP:
				mouse.setClick(event.button.button-1, false);
				break;
			default: /*other actions to be implemented in the future*/ break;
		}
	}else{
		//When there is no recognized event at this instant
	}
}

void EventHandler::resetEscape(){
	keyboard.set(KeyboardHandler::ESCAPE) = false;
}

bool EventHandler::quit() const{
	return quitgame;
}

const KeyboardHandler& EventHandler::getKeyboard() const{
	return keyboard;
}
const MouseHandler& EventHandler::getMouse() const{
	return mouse;
}


