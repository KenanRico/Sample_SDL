#include <SDL2/SDL.h>
#include "sprite.h"
#include "eventhandler.h"
#include "keyboardhandler.h"
#include "bulletmanager.h"

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
		enum SpriteSize{WALKSHEET=0, SPRINTSHEET=1, JUMPSHEET=2, WALKSPRITE=3, SPRINTSPRITE=4, JUMPSPRITE=5};
		enum Dimension{W=0, H=1};
		BulletManager p_bullets;
		
	public: 
		Player() = delete;
		~Player();
		Player(const Player&) = delete;
		Player& operator=(const Player&) = delete;
	public:
		Player(SDL_Renderer*, const char*, const char*, int,int,int,int,int,int,int,int, int,int,int,int);
	public:
		void renderSprite() override;
		void updateSprite() override; //update sprite on states
	private:
		void updateState(const EventHandler&); //update states (or attributes) on p_action
		void actionUpdate();
		void jumpUpdate();
		void onGroundUpdate();

		void updateActionBasedOnEvent(const EventHandler&);
};

#endif
