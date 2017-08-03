#include "objectlayerobject.h"
#include <iostream>


ObjectLayerObject::ObjectLayerObject(int _id, int _x, int _y): ID(_id), x0(_x), y0(_y), x(_x), y(_y){;}

ObjectLayerObject::~ObjectLayerObject(){;}

void ObjectLayerObject::updateObject(int offX, int offY){
	x = x0-offX;
	//y = y0-offY;
}

int ObjectLayerObject::angleLeft() const{
	return 1;
}
int ObjectLayerObject::angleRight() const{
	return 1;
}


void ObjectLayerObject::printInfo() const{ //debug. remove
	std::cout<<ID<<" "<<x<<" "<<y<<"\n";	
}
