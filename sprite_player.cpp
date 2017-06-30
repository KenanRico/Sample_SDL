#include <SDL2/SDL.h>
#include "sprite_player.h"
#include "sprite.h"
#include "gamesystem.h"

#include <iostream> //for debugging, remove when done

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
			_acceleration = 1;
			_deceleration = 10;
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
	public:
		PlayerState(): speed_h(0), speed_v(0), direction(1), in_air(false){;}
		~PlayerState(){;}
		PlayerState(const PlayerState&) = delete;
		PlayerState& operator=(const PlayerState&) = delete;

};
class Player::PlayerAction{
	public:
		bool ctrl;
		bool d;
		bool a;
		bool space;
		bool j;
	public:
		bool _walk;
		bool _sprint;
		int _movedirection;
		bool _jump;
		bool _attack;
	public:
		PlayerAction(): ctrl(false),d(false),a(false),space(false),j(false),_walk(false),_sprint(false),_movedirection(0),_jump(false),_attack(false){;}
		~PlayerAction(){;}
		PlayerAction(const PlayerAction&) = delete;
		PlayerAction& operator=(const PlayerAction&) = delete;
	public:
		void updateActionBasedOnEvent(){
			_walk = ((d||a)&&!ctrl);
			_sprint = ((d||a)&&ctrl);
			if(a==true&&d==true) ;
			else if(a==true) _movedirection=-1;
			else if(d==true) _movedirection=1;
			else _movedirection=0;
			_jump = space;
			_attack = j;


			std::cout<<"walk: "<<_walk<<" sprint: "<<_sprint<<" movedirection: "<<_movedirection<<" jump: "<<_jump<<" attack: "<<_attack<<std::endl;
		}
};




Player::Player(SDL_Renderer*& g_renderer, const char* img, int _sx,int _sy,int _sw,int _sh,int _dx,int _dy,int _dw,int _dh, int a,int s,int i,int d):
Sprite(g_renderer,img,_sx,_sy,_sw,_sh,_dx,_dy,_dw,_dh), p_attribute(new PlayerAttribute(a,s,i,d)), p_state(new PlayerState), p_action(new PlayerAction)
{;}

Player::~Player(){
	delete p_attribute;
	delete p_state;
	delete p_action;

}




void Player::updateState(){
	if(!p_state->in_air){
		if(p_action->_walk){std::cout<<"speed_h:"<<p_state->speed_h<<" acc:"<<p_attribute->_acceleration<<" topwalkspeed:"<<p_attribute->_topwalkspeed<<std::endl;
			(p_state->speed_h+p_attribute->_acceleration > p_attribute->_topwalkspeed)?
			 p_state->speed_h=p_attribute->_topwalkspeed : p_state->speed_h+=p_attribute->_acceleration;
		}else if(p_action->_sprint){
			(p_state->speed_h+p_attribute->_acceleration*2 > p_attribute->_topwalkspeed)?
			 p_state->speed_h=p_attribute->_topwalkspeed : p_state->speed_h+=p_attribute->_acceleration*2;
		}else{
			(p_state->speed_h-p_attribute->_deceleration < 0)?
			 0 : p_state->speed_h-=p_attribute->_deceleration;
		}
		if(p_action->_jump){
			p_state->speed_v = p_attribute->_jumpspeed;
			p_state->in_air = true;
		}else;
	}else{
		(p_state->speed_h-p_attribute->_deceleration/4 < 0)?
		 0 : p_state->speed_h-=p_attribute->_deceleration/4;
		(p_state->speed_v-9 < 0)?
		 0 : p_state->speed_h-=9;
		if(p_state->speed_v==0){
			p_state->in_air = false;
		}else;
	}
	if(p_action->_movedirection!=0){
		p_state->direction = p_action->_movedirection;
	}else;
	std::cout<<p_state->speed_h<<" "<<p_state->speed_v<<" "<<p_state->in_air<<std::endl;
}

void Player::updateSprite(){
	int sx = s_srcRect->x;
	int sy = s_srcRect->y;
	int sw = s_srcRect->w;
	int sh = s_srcRect->h;
	int dx = s_dstRect->x;
	int dy = s_dstRect->y;
	int dw = s_dstRect->w;
	int dh = s_dstRect->h;
	int pm = GameSystem::PixToMetre;
	dx += p_state->speed_h*pm/60*p_state->direction;
	dy += p_state->speed_v*pm/60*p_state->in_air;
	//setSrcRect();
	setDstRect(dx,dy,dw,dh);

}
void Player::setAction(const SDL_Event* event){
	//after polling
	switch(event->type){
		case SDL_KEYDOWN:
			switch(event->key.keysym.sym){
				case SDLK_LCTRL: p_action->ctrl = true; break;
				case SDLK_d: p_action->d = true; break;
				case SDLK_a: p_action->a = true; break;
				case SDLK_SPACE: p_action->_jump = true; break;
				case SDLK_j: p_action->j = true; break;
				default: /*other keys to be implemented in the future*/ break;
			}
			break;
		case SDL_KEYUP:
			switch(event->key.keysym.sym){
				case SDLK_LCTRL: p_action->ctrl = false; break;
				case SDLK_d: p_action->d = false; break;
				case SDLK_a: p_action->a = false; break;
				case SDLK_SPACE: p_action->_jump = false; break;
				case SDLK_j: p_action->j = false; break;
				default: /*every KEYUP correspond to a KEYDOWN*/ break;
			}
			break;
		default: /*other actions to be implemented in the future*/
			break;
	}
	p_action->updateActionBasedOnEvent();
}

void Player::renderSprite(){
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	switch(p_state->direction){
		case 0: flip = SDL_FLIP_NONE; break;
		case -1: flip = SDL_FLIP_HORIZONTAL; break;
		case 1: break;
		default: break;
	}
	SDL_RenderCopyEx(*s_mainRendererPointer, s_texture, s_srcRect, s_dstRect, 0, 0, flip);
}


