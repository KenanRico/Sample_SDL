#include <SDL2/SDL.h>
#include "menu_button.h"
#include "eventhandler.h"
#include "mousehandler.h"

#include <iostream> //remove


Button::Button(SDL_Renderer* g_renderer, const char* img_path, int sx,int sy,int sw,int sh, int dx,int dy,int dw,int dh):
MenuItem(g_renderer, img_path, sx,sy,sw,sh, dx,dy,dw,dh),
b_hoveredover(false),
b_framecounter(0){
	;
}

Button::~Button(){
	;
}


void Button::render(){
	//if hightlighted, rerender new button at highlight phase
	//rerender new button at "phase"
	if(b_framecounter%6==0){
		if(m_clicked){
			rotateSprite();
		}else{
			if(b_hoveredover){
				selectHoveredSprite(); //if src_Rect reach end, set m_clicked to false
			}else{
				selectFirstNormalSprite();//also set b_hoveredover to false
			}
		}
	}else;
	++b_framecounter;
	SDL_RenderCopy(m_mainRendererPointer, m_texture, m_srcRect, m_dstRect);

	std::cout<<b_framecounter<<std::endl;//remove
	
}

void Button::onEvent(const EventHandler& event){
	const MouseHandler& mouse = event.getMouse();
	int mouseX = mouse.getX();
	int mouseY = mouse.getY();
	int mouseClickX = mouse.getClickX();
	int mouseClickY = mouse.getClickY();
	if(mouseX>=m_dstRect->x&&mouseX<=m_dstRect->x+m_dstRect->w && mouseY>=m_dstRect->y&&mouseY<=m_dstRect->y+m_dstRect->h){
		b_hoveredover = true;
	}else;
	if(mouse[MouseHandler::LEFT] &&
	mouseClickX>=m_dstRect->x &&
	mouseClickX<=m_dstRect->x+m_dstRect->w &&
	mouseClickY>=m_dstRect->y &&
	mouseClickY<=m_dstRect->y+m_dstRect->h){
		m_clicked = true;
	}
	
	//check if mouse is hovering over the button while not being clicked, b_highlighted=true if yes, false if not
	//check if mouse is clicked while the button is already highlighted (that's pretty smart), m_clicked=true if yes, false if not
	//if(m_clicked){repeatedly render button's different phrase}else;
}


void Button::rotateSprite(){
	if(m_srcRect->x+160<=440){
		m_srcRect += 160;
	}else{
		m_triggered = true;
		selectFirstNormalSprite();
	}
}

void Button::selectFirstNormalSprite(){
	m_srcRect->x = 0;
	m_clicked = false;
}

void Button::selectHoveredSprite(){


	b_hoveredover = false;

}
