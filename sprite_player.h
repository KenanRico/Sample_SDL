#include <SDL2/SDL.h>
#include "sprite.h"


#ifndef SPRITE_PLAYER_H
#define SPRITE_PLAYER_H
class Player : public Sprite{
	private: 
		class PlayerAttribute;
		class PlayerState;
		class PlayerAction;
	private: 
		PlayerAttribute* p_attribute;
		PlayerState* p_state;
		PlayerAction* p_action; //PlayerAction is a class that translate user input into character action
	public: 
		Player() = delete;
		~Player();
		Player(const Player&) = delete;
		Player& operator=(const Player&) = delete;
	public:
		Player(SDL_Renderer*&, const char*, int,int,int,int,int,int,int,int, int,int,int,int);
	public:
		void renderSprite();
		void setAction(const SDL_Event*);
		void updateSprite(); //update sprite on states
	private:
		void updateState(); //update states (or attributes) on p_action
};
#endif
