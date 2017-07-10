#include <SDL2/SDL.h>
#include "menu_button.h"
#include "eventhandler.h"
#include "mousehandler.h"



class Button::ButtonState{
	public:
		bool hovered;
		bool clicked;
		bool triggered;
	public:
		ButtonState(): hovered(false), clicked(false), triggered(false){;}
		~ButtonState(){;}
		ButtonState(const ButtonState&) = delete;
		ButtonState& operator=(const ButtonState&) = delete;
};


Button::Button(SDL_Renderer* g_renderer, const char* img_path, int sx,int sy,int sw,int sh, int dx,int dy,int dw,int dh):
MenuItem(g_renderer, img_path, sx,sy,sw,sh, dx,dy,dw,dh),
b_state(new ButtonState()){
	;
}

Button::~Button(){
	delete b_state;
}

void Button::render(){
	SDL_RenderCopy(m_mainRendererPointer, m_texture, m_srcRect, m_dstRect);
}

void Button::update(const EventHandler& event){
	updateState(event);
	updateSprite();
}

void Button::updateState(const EventHandler& event){
	if(!b_state->clicked){
		const MouseHandler& mouse = event.getMouse();
		int mouseX = mouse.getX();
		int mouseY = mouse.getY();
		int mouseClickX = mouse.getClickX();
		int mouseClickY = mouse.getClickY();
		bool mouseClick = mouse[MouseHandler::LEFT];
		b_state->hovered = !mouseClick && (mouseX>=m_dstRect->x&&mouseX<=m_dstRect->x+m_dstRect->w) && (mouseY>=m_dstRect->y&&mouseY<=m_dstRect->y+m_dstRect->h);
		b_state->clicked = mouseClick && (mouseClickX>=m_dstRect->x&&mouseClickX<=m_dstRect->x+m_dstRect->w) && (mouseClickY>=m_dstRect->y&&mouseClickY<=m_dstRect->y+m_dstRect->h);
	}else;
	++m_framecounter;
}
void Button::updateSprite(){
	if(m_framecounter%4==0){
		if(b_state->clicked){
			if(m_srcRect->x+158 < m_imageW){
			m_srcRect->x += 158;
			}else{
				//m_srcRect->x = 0;
				b_state->triggered = true;
				b_state->clicked = false;
			}
		}else if(b_state->hovered){
			m_srcRect->x = 158;
	
		}else{
			m_srcRect->x = 0;
		}
	}else;
}

bool Button::triggered() const{
	return b_state->triggered;
}






/*
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
	
}

void Button::update(const EventHandler& event){
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

*/
