#include <SDL2/SDL.h>
#include "menu_button.h"
#include "eventhandler.h"



Button::Button(SDL_Renderer* g_renderer, const char* img_path, int sx,int sy,int sw,int sh, int dx,int dy,int dw,int dh, int phases):
MenuItem(g_renderer, img_path, sx,sy,sw,sh, dx,dy,dw,dh),
b_phases(phases),
b_highlighted(false){
	;
}

Button::~Button(){
	;
}


void Button::render(int phase){
	//clean button
	//if hightlighted, rerender new button at highlight phase
	//rerender new button at "phase"
	if(phase==b_phases-1){
		m_triggered = false;
	}else;
}

void Button::onEvent(const EventHandler& event){
	//check if mouse is hovering over the button while not being clicked, b_highlighted=true if yes, false if not
		if(event.getMouseX			


	//check if mouse is clicked while the button is already highlighted (that's pretty smart), m_triggered=true if yes, false if not
	//if(m_triggered){repeatedly render button's different phrase}else;
}

