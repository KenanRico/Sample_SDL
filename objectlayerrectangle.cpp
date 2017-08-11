#include "objectlayerobject.h"
#include "objectlayerrectangle.h"
#include "gamesystem.h"


ObjectLayerRectangle::ObjectLayerRectangle(int _id, int _x, int _y, int _w, int _h):
ObjectLayerObject(_id, _x, _y), width(_w), height(_h){
	;
}

ObjectLayerRectangle::~ObjectLayerRectangle(){;}


bool ObjectLayerRectangle::onContact(int side, int y1, int y2, int x1, int x2) const{
	bool result = false;
	try{
		switch(side){
			case ObjectLayerObject::TOP: 
				result = above(y1,y2,x1,x2);
				break;
			case ObjectLayerObject::BOTTOM: 
				result = below(y1,y2,x1,x2);
				break;
			case ObjectLayerObject::LEFT: 
				result = leftof(y1,y2,x1,x2);
				break;
			case ObjectLayerObject::RIGHT: 
				result = rightof(y1,y2,x1,x2);
				break;
			default:
				throw "Unrecognized side in onContact";
				break;
		}
	}catch(const char* Err){
		GameSystem::writeErrorMessage(Err);
		result = false;
	}
	return result;
}

bool ObjectLayerRectangle::above(int top, int bottom, int left, int right) const{
	bool result = false;
	if(right>x&&right<(x+width) || left<(x+width)&&left>x){
		if(y < top){
			if(top-(y+height)<=1){
				result = true;
			}else;
		}else;
	}else;
	return result;
}
bool ObjectLayerRectangle::below(int top, int bottom, int left, int right) const{
	bool result = false;
	if(right>x&&right<(x+width) || left<(x+width)&&left>x){
		if(y+height > bottom){
			if(y-bottom<=1){
				result = true;
			}else;
		}else;
	}else;
	return result;
}
bool ObjectLayerRectangle::leftof(int top, int bottom, int left, int right) const{
	bool result = false;
	if(bottom>y&&bottom<(y+height) || top<(y+height)&&top>y){
		if(left>x){
			if(left-(x+width)<=1){
				result = true;
			}else;
		}else;
	}else;
	return result;
}
bool ObjectLayerRectangle::rightof(int top, int bottom, int left, int right) const{
	bool result = false;
	if(bottom>y&&bottom<(y+height) || top<(y+height)&&top>y){
		if(right<(x+width)){
			if(x-right<=1){
				result = true;
				std::cout<<"This object is contacting sprite on its right: "<<ObjectLayerObject::ID<<". Sprite bottom: "<<bottom<<". Object top: "<<y<<"\n"; //remove
			}else;
		}else;
	}else;
	return result;
}


int ObjectLayerRectangle::top() const{
	return y;
}
int ObjectLayerRectangle::bottom() const{
	return y+height;
}
int ObjectLayerRectangle::left() const{
	return x;
}
int ObjectLayerRectangle::right() const{
	return x+width;
}
