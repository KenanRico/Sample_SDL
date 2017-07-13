#include <SDL2/SDL.h>
#include "menuitem.h"
#include "eventhandler.h"

#ifndef SPRITE_BUTTON_H
#define SPRITE_BUTTON_H
class Button: public MenuItem{
	private: 
		class ButtonState;
	private:
		ButtonState* b_state;
	public:
		Button() = delete;
		~Button();
		Button(const Button&) = delete;
		Button& operator=(const Button&) = delete;
	public:
		Button(SDL_Renderer*, const char*, int,int,int,int, int,int,int,int);
		
	public:
		void render() override;
		void update(const EventHandler&) override;
		bool triggered() const override;
	private:
		void updateState(const EventHandler&);
		void updateSprite();


		//void rotateSprite();
		//void selectHoveredSprite();
		//void selectFirstNormalSprite();
		
};
#endif
