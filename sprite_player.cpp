#include <SDL2/SDL.h>
#include "sprite_player.h"
#include "sprite.h"
#include "gamesystem.h"
#include "eventhandler.h"
#include "keyboardhandler.h"

#include <iostream> //remove

class Player::PlayerAttribute{
	private:
		int agility;
		int strength;
		int intelligence;
		int dexterity;
	public:
		int _jumpspeed;
		int _acceleration;
		int _deceleration;
		int _topwalkspeed;
		int _topsprintspeed;
		int _attackstrength;
		int _critchance;
		int _critstrength;
	public:
		PlayerAttribute() = delete;
		~PlayerAttribute(){;}
		PlayerAttribute(const PlayerAttribute&) = delete;
		PlayerAttribute& operator=(const PlayerAttribute&) = delete;
	public:
		PlayerAttribute(int a, int s, int i, int d): agility(a), strength(s), intelligence(i), dexterity(d){
			//all values below are sample value; will change later
			_jumpspeed = 5;
			_acceleration = 3;//per second, applied every 1/3 second (per 20 frames)
			_deceleration = 10;//per second, applied every 1/10 second (per 6 frames)
			_topwalkspeed = 6;
			_topsprintspeed = 12;
			_attackstrength = 0;
			_critchance = 0;
			_critstrength = 0;
		}
};
class Player::PlayerState{
	public:
		int speed_h;
		int speed_v;
		int direction;
		bool in_air;
		SDL_RendererFlip spriteflip;
	public:
		PlayerState(): speed_h(0), speed_v(0), direction(1), in_air(false), spriteflip(SDL_FLIP_NONE){;}
		~PlayerState(){;}
		PlayerState(const PlayerState&) = delete;
		PlayerState& operator=(const PlayerState&) = delete;

};
class Player::PlayerAction{
	public:
		bool _walk;
		bool _sprint;
		int _movedirection;
		bool _jump;
		bool _attack;
	public:
		PlayerAction(): _walk(false),_sprint(false),_movedirection(0),_jump(false),_attack(false){;}
		~PlayerAction(){;}
		PlayerAction(const PlayerAction&) = delete;
		PlayerAction& operator=(const PlayerAction&) = delete;
};



Player::Player(SDL_Renderer*& g_renderer, const char* img, int _sx,int _sy,int _sw,int _sh,int _dx,int _dy,int _dw,int _dh, int a,int s,int i,int d):
Sprite(g_renderer,img,_sx,_sy,_sw,_sh,_dx,_dy,_dw,_dh), p_attribute(new PlayerAttribute(a,s,i,d)), p_state(new PlayerState), p_action(new PlayerAction)
{;}

Player::~Player(){
	delete p_attribute;
	delete p_state;
	delete p_action;
}



void Player::updateState(const EventHandler& event){
	updateActionBasedOnEvent(event);
	if(!p_state->in_air){
		onGroundSpeedChange();
		std::cout<<p_state->speed_h<<" "<<p_state->speed_v<<" "<<p_state->in_air<<std::endl;//remove
		checkJump();
	}else;
	if(p_state->in_air){
		inAirSpeedChange();
		checkLand();
	}else;
	++s_framecounter;
	//We need a procedure here to reset framecounter to 0 when reaching least common multiple of all frames-dependent updates (to prevent overflow in case someone plays this game for straight 20k hours without stopping)
}

void Player::onGroundSpeedChange(){
	if(p_state->speed_h==0){
		p_state->direction = p_action->_movedirection;
	}else;
	if(p_action->_movedirection==0){
		if(s_framecounter%5==0){
			(p_state->speed_h-1 > 0)?
			--p_state->speed_h : p_state->speed_h=0;
		}else;	
	}else{
		if(p_state->direction==p_action->_movedirection){
			if(p_action->_walk){
				if(s_framecounter%7==0){
					(p_state->speed_h+1 < p_attribute->_topwalkspeed)?
					++p_state->speed_h : p_state->speed_h=p_attribute->_topwalkspeed;
				}else;
			}else if(p_action->_sprint){
				if(s_framecounter%5==0){
					(p_state->speed_h+1 < p_attribute->_topsprintspeed)?
					++p_state->speed_h : p_state->speed_h=p_attribute->_topsprintspeed;
				}else;
			}else;
		}else{
			if(p_action->_walk){
				if(s_framecounter%4==0){
					(p_state->speed_h-1 > 0)?
					--p_state->speed_h : p_state->speed_h=0;
				}else;
			}else if(p_action->_sprint){
				if(s_framecounter%3==0){
					(p_state->speed_h-1 > 0)?
					--p_state->speed_h : p_state->speed_h=0;
				}
			}else;
		}
	}
}
void Player::checkJump(){
	if(p_action->_jump){
		p_state->in_air = true;
		p_state->speed_v = -p_attribute->_jumpspeed;
	}else;
}

void Player::inAirSpeedChange(){
	if(s_framecounter%5==0){
		(p_state->speed_h-1 > 0) ? --p_state->speed_h : p_state->speed_h=0;
	}else;
	if(s_framecounter%10==0){
		(p_state->speed_v+1 <= 10)?
		 ++p_state->speed_v : p_state->speed_v=0;
	}else;
}
void Player::checkLand(){
//implement later on
	if(false){
		p_state->in_air = false;
	}else;
}


void Player::updateSprite(){
	int pm = GameSystem::PixToMetre;
	s_srcRect->x = (s_srcRect->x+40>300)?3:s_srcRect->x+40;
	s_dstRect->x += p_state->speed_h*pm/60*p_state->direction;
	s_dstRect->y += p_state->speed_v*pm/60*p_state->in_air;
	//setSrcRect();

}

void Player::updateActionBasedOnEvent(const EventHandler& event){
	p_action->_walk = ((event.getKeyboard(KeyboardHandler::A)||event.getKeyboard(KeyboardHandler::D))&&!event.getKeyboard(KeyboardHandler::CTRL));
	p_action->_sprint = ((event.getKeyboard(KeyboardHandler::A)||event.getKeyboard(KeyboardHandler::D))&&event.getKeyboard(KeyboardHandler::CTRL));
	if(event.getKeyboard(KeyboardHandler::A)==true&&event.getKeyboard(KeyboardHandler::D)==true) ;
	else if(event.getKeyboard(KeyboardHandler::A)==true) p_action->_movedirection = -1;
	else if(event.getKeyboard(KeyboardHandler::D)==true) p_action->_movedirection = 1;
	else p_action->_movedirection=0;
	p_action->_jump = event.getKeyboard(KeyboardHandler::K);
	p_action->_attack = event.getKeyboard(KeyboardHandler::J);
	std::cout<<"walk: "<<p_action->_walk<<" sprint: "<<p_action->_sprint<<" movedirection: "<<p_action->_movedirection<<" jump: "<<p_action->_jump<<" attack: "<<p_action->_attack<<std::endl;//remove
}

void Player::renderSprite(){
	switch(p_state->direction){
		case 1: p_state->spriteflip = SDL_FLIP_NONE; break;
		case -1: p_state->spriteflip = SDL_FLIP_HORIZONTAL; break;
		case 0: break;
		default: break;
	}
	SDL_RenderCopyEx(*s_mainRendererPointer, s_texture, s_srcRect, s_dstRect, 0, 0, p_state->spriteflip);
}


