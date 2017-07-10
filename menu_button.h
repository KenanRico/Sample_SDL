#include <SDL2/SDL.h>
#include "menuitem.h"
#include "eventhandler.h"


#ifndef SPRITE_BUTTON_H
#define SPRITE_BUTTON_H
class Button: public MenuItem{
	private:
		bool b_hoveredover;
		int b_framecounter;
	public:
		Button() = delete;
		~Button();
		Button(const Button&) = delete;
		Button& operator=(const Button&) = delete;
	public:
		Button(SDL_Renderer*, const char*, int,int,int,int, int,int,int,int);
		
	public:
		void render() override;
		void onEvent(const EventHandler&) override;
	
	private:
		void rotateSprite();
		void selectHoveredSprite();
		void selectFirstNormalSprite();
		
};
#endif
