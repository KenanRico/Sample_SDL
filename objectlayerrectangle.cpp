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
	if(left>=x && right<=x+width){
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
	if(left>=x && right<=x+width){
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
	if(top>=y && bottom<=(y+height)){
		if(x<left){
			if(left-(x+width)<=1){
				result = true;
			}else;
		}else;
	}else;
	return result;
}
bool ObjectLayerRectangle::rightof(int top, int bottom, int left, int right) const{
	bool result = false;
	if(top>=y && bottom<=(y+height)){
		if((x+height)>right){
			if(x-right<=1){
				result = true;
			}else;
		}else;
	}else;
	return result;
}
