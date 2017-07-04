#include <SDL2/SDL.h>
#include "keyboardhandler.h"




KeyboardHandler::KeyboardHandler() : keys_pressed(new bool[9]){
	for(int i=0; i<9; ++i){
		keys_pressed[i] = false;
	}
}


KeyboardHandler::~KeyboardHandler(){
	delete[] keys_pressed;
}


bool& KeyboardHandler::operator[](int key){
	return keys_pressed[key];
}
