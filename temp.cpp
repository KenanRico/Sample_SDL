

void Player::updateState(){
	if(!p_state->in_air){
		onGroundSpeedChange();
		checkJump();

	}else;
	if(p_state->in_air){
		inAirSpeedChange();
		checkLand();
	}else;
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
			}else if(p_action->sprint){
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
			}else if(p_action->sprint){
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


