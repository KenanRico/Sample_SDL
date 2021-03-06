#include <SDL2/SDL.h>
#include "sprite_player.h"
#include "sprite.h"
#include "gamesystem.h"
#include "eventhandler.h"
#include "keyboardhandler.h"
#include "bulletmanager.h"
#include "bullet.h"

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
			_jumpspeed = 16;
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
		bool attacking;
		bool jumping_up;
		SDL_RendererFlip spriteflip;
	public:
		PlayerState(): speed_h(0), speed_v(0), direction(1), in_air(false), attacking(false), jumping_up(false), spriteflip(SDL_FLIP_NONE){;}
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



Player::Player(SDL_Renderer* g_renderer, const char* nm, const char* img, int _sx,int _sy,int _sw,int _sh,int _dx,int _dy,int _dw,int _dh, int a,int s,int i,int d):
Sprite(g_renderer,nm,img,_sx,_sy,_sw,_sh,_dx,_dy,_dw,_dh), 
p_attribute(new PlayerAttribute(a,s,i,d)), 
p_state(new PlayerState), 
p_action(new PlayerAction){
	;
}

Player::~Player(){
	delete p_attribute;
	delete p_state;
	delete p_action;
}



void Player::updateState(const EventHandler& event){
	++s_framecounter;
	updateActionBasedOnEvent(event);
	actionUpdate();
	s_collision.updateCollisionInfo();
	jumpUpdate();
	onGroundUpdate();
	p_bullets.update();
	//We need a procedure here to reset framecounter to 0 when reaching least common multiple of all frames-dependent updates (to prevent overflow in case someone plays this game for straight 20k hours without stopping)
}

void Player::actionUpdate(){
	if(p_action->_attack){
		p_state->attacking = true;
		p_bullets.shoot(new Bullet(/*path*/"assets/button_yellow.png",
						/*direction*/p_state->direction,
						/*posX*/s_dstRect->x+s_dstRect->w/2, 
						/*posY*/s_dstRect->y+s_dstRect->h/2, 
						/*speedX*/p_state->speed_h, 
						/*speedY*/p_state->speed_v, 
						&s_framecounter,
						s_mainRendererPointer));
	}else;
	if(p_action->_jump){
		p_state->jumping_up = true;
	}else;
}

void Player::jumpUpdate(){
	if(s_collision.getCollisionInfo().bottom){
		if(p_state->in_air){
			if(p_state->speed_v>0){
				p_state->in_air = false;
				p_state->speed_v = 0;
				s_srcRect->x = 0;
			}else if(p_state->speed_v<0){
				s_srcRect->x = 40;
			}else;
		}else{
			if(p_action->_jump){
				p_state->in_air = true;
				s_srcRect->x = 40;
				p_state->speed_v = -p_attribute->_jumpspeed;
			}else;
		}
	}else{
		if(p_state->in_air){
			if(s_framecounter%1==0){
				++p_state->speed_v;
			}else;
		}else{
			p_state->in_air = true;
			s_srcRect->x = 40;
			//GameSystem::writeErrorMessage("huhuhuh");
		}
	}
}

void Player::onGroundUpdate(){
	if(p_state->speed_h==0){
		p_state->direction = (p_action->_movedirection!=0) ? p_action->_movedirection : p_state->direction;
	}else;
	if(p_action->_movedirection==0){
		if(s_framecounter%3==0){
			(p_state->speed_h-1 > 0)?
			--p_state->speed_h : p_state->speed_h=0;
		}else;
	}else{
		if(p_action->_movedirection==-1 && !s_collision.getCollisionInfo().left || p_action->_movedirection==1 && !s_collision.getCollisionInfo().right){
			if(p_state->direction==p_action->_movedirection){
				if(p_action->_walk){
					if(s_framecounter%8==0){
						(p_state->speed_h+1 < p_attribute->_topwalkspeed)? ++p_state->speed_h : p_state->speed_h=p_attribute->_topwalkspeed;
					}else;
				}else if(p_action->_sprint){
					if(s_framecounter%6==0){
						(p_state->speed_h+1 < p_attribute->_topsprintspeed)? ++p_state->speed_h : p_state->speed_h=p_attribute->_topsprintspeed;
					}else;
				}else;
			}else{
				if(p_action->_walk){
					if(s_framecounter%2==0){
						(p_state->speed_h-1 > 0) ? --p_state->speed_h : p_state->speed_h=0;
					}else;
				}else if(p_action->_sprint){
					if(s_framecounter%1==0){
						(p_state->speed_h-1 > 0) ? --p_state->speed_h : p_state->speed_h=0;
					}else;
				}else;
			}
		}else{
			p_state->speed_h = 0;
			//extra animation for collision
		}
	}
}

void Player::updateSprite(){
	int pm = GameSystem::PixToMetre;
	if(!p_state->in_air){
		if(p_state->speed_h!=0){
			if(p_state->attacking){
				s_srcRect->y=100;
				p_state->attacking = p_action->_attack;
			}else{
				s_srcRect->y = 50;
			}
			if(s_framecounter%(15-((p_state->speed_h<7)?p_state->speed_h+1:p_state->speed_h))==0){
				if(p_state->attacking){
					s_srcRect->x = 280;
					p_state->attacking = p_action->_attack;
				}else{
					s_srcRect->x = (s_srcRect->x+40>300)?0:s_srcRect->x+40;
				}
			}else;
			if(s_dstRect->x<150&&p_state->direction==-1 || s_dstRect->x>440&&p_state->direction==1){
				s_offsetX += p_state->speed_h*pm/60*p_state->direction;
			}else{
				s_dstRect->x += p_state->speed_h*pm/60*p_state->direction;
			}
		}else{
			//standing
			if(p_state->attacking){
				s_srcRect->x = 280;
				s_srcRect->y = 100;
				p_state->attacking = p_action->_attack;
			}else{
				s_srcRect->x = (s_srcRect->x>150)?0:s_srcRect->x;
				s_srcRect->y = 0;
			}
			if(s_framecounter%12==0){
				if(p_state->attacking){
					s_srcRect->x = 280;
					p_state->attacking = p_action->_attack;
				}else{
					s_srcRect->x = (s_srcRect->x+40>150)?0:s_srcRect->x+40;
				}
			}else;
		}
	}else{
		s_srcRect->y = 100;
		if(s_srcRect->x<200){
			if(s_framecounter%6==0){
				if(p_state->attacking){
					s_srcRect->x = 280;
					p_state->attacking = p_action->_attack;
				}else{
					s_srcRect->x += 40;
				}
			}else;
		}else if(s_srcRect->x==280){
			if(p_state->attacking){
				s_srcRect->x = 280;
				p_state->attacking = p_action->_attack;
			}else{
				s_srcRect->x = 80;
			}
		}else;
		if(s_dstRect->x<150&&p_state->direction==-1 || s_dstRect->x>440&&p_state->direction==1){
			s_offsetX += p_state->speed_h*pm/60*p_state->direction;
		}else{
			s_dstRect->x += p_state->speed_h*pm/60*p_state->direction;
		}
		if(s_offsetY<200&&p_state->direction==-1 || s_offsetY>440&&p_state->direction==1 || false){
			s_offsetY += p_state->speed_v*pm/60*p_state->in_air;
		}else{
			s_dstRect->y += p_state->speed_v*pm/60*p_state->in_air;
		}
		//jump
	}
			if(s_dstRect->y+s_dstRect->h > s_collision.getCollisionInfo().highestbottom){
				s_dstRect->y = s_collision.getCollisionInfo().highestbottom-s_dstRect->h;
			}else;
			if(s_dstRect->y < s_collision.getCollisionInfo().lowesttop){
				s_dstRect->y = s_collision.getCollisionInfo().lowesttop;
			}else;
}

void Player::updateActionBasedOnEvent(const EventHandler& event){
	const KeyboardHandler& keyboard = event.getKeyboard();
	p_action->_walk = ((keyboard[KeyboardHandler::A]||keyboard[KeyboardHandler::D])&&!keyboard[KeyboardHandler::CTRL]);
	p_action->_sprint = ((keyboard[KeyboardHandler::A]||keyboard[KeyboardHandler::D])&&keyboard[KeyboardHandler::CTRL]);
	if(keyboard[KeyboardHandler::A]==true&&keyboard[KeyboardHandler::D]==true) ;
	else if(keyboard[KeyboardHandler::A]==true) p_action->_movedirection = -1;
	else if(keyboard[KeyboardHandler::D]==true) p_action->_movedirection = 1;
	else p_action->_movedirection=0;
	p_action->_jump = keyboard[KeyboardHandler::K];
	p_action->_attack = keyboard[KeyboardHandler::J];
	//std::cout<<"walk: "<<p_action->_walk<<" sprint: "<<p_action->_sprint<<" movedirection: "<<p_action->_movedirection<<" jump: "<<p_action->_jump<<" attack: "<<p_action->_attack<<std::endl;//remove
	//std::cout<<event.getMouse().getX()<<" "<<event.getMouse().getY()<<" "<<event.getMouse()[0]<<" "<<event.getMouse()[1]<<" "<<event.getMouse()[2]<<" "<<event.getMouse().getClickX()<<" "<<event.getMouse().getClickY()<<std::endl;//remove
}

void Player::renderSprite(){
	switch(p_state->direction){
		case 1: p_state->spriteflip = SDL_FLIP_NONE; break;
		case -1: p_state->spriteflip = SDL_FLIP_HORIZONTAL; break;
		case 0: break;
		default: break;
	}
	SDL_RenderCopyEx(s_mainRendererPointer, s_texture, s_srcRect, s_dstRect, 0, 0, p_state->spriteflip);
	p_bullets.renderAllBullets();
}


