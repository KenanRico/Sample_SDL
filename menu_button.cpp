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
	if(b_state->triggered){
		b_state->clicked = false;
	}else;
	if(!b_state->clicked){
		const MouseHandler& mouse = event.getMouse();
		int mouseX = mouse.getX();
		int mouseY = mouse.getY();
		int mouseClickX = mouse.getClickX();
		int mouseClickY = mouse.getClickY();
		bool mouseClick = mouse[MouseHandler::LEFT];
		b_state->hovered = !mouseClick && (mouseX>=m_dstRect->x&&mouseX<=m_dstRect->x+m_dstRect->w) && (mouseY>=m_dstRect->y&&mouseY<=m_dstRect->y+m_dstRect->h);
		b_state->clicked = mouseClick && (mouseClickX>=m_dstRect->x&&mouseClickX<=m_dstRect->x+m_dstRect->w) && (mouseClickY>=m_dstRect->y&&mouseClickY<=m_dstRect->y+m_dstRect->h);
	}else{
		//skip this function once button is clicked to allow animation to run
	}
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
