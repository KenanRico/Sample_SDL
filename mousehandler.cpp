#include "mousehandler.h"


MouseHandler::MouseHandler(): click(new bool[3]), position(new int[2]()), clickposition(new int[2]()){
	for(int i=0; i<3; ++i){
		click[i] = false;
	}
}

MouseHandler::~MouseHandler(){
	delete[] click;
	delete[] position;
	delete[] clickposition;
}


void MouseHandler::setClick(int button, bool value){
	click[button] = value;
}

void MouseHandler::setPosition(int _x, int _y){
	position[X] = _x;
	position[Y] = _y;
}

void MouseHandler::setClickPosition(int _x, int _y){
	clickposition[X] = _x;
	clickposition[Y] = _y;
}

int MouseHandler::getX() const{
	return position[X];
}
int MouseHandler::getY() const{
	return position[Y];
}

int MouseHandler::getClickX() const{
	return clickposition[X];
}
int MouseHandler::getClickY() const{
	return clickposition[Y];
}

bool MouseHandler::operator[](int button) const{
	return click[button];
}
