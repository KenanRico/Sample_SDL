#include "objectlayer.h"
#include <vector>



ObjectLayer::ObjectLayer(const char* _name): name(_name){
	;
}

ObjectLayer::~ObjectLayer(){
	for(std::vector<ObjectLayerObject*>::iterator i=objects.begin(); i<objects.end(); ++i){
		delete *i;
	}
}


void ObjectLayer::insertObject(ObjectLayerObject* obj){
	objects.push_back(obj);
}

const std::vector<ObjectLayerObject*>& ObjectLayer::getObjects() const{
	return objects;
}

void ObjectLayer::updateObjectLayer(int screenOffsetX, int screenOffsetY){
	for(std::vector<ObjectLayerObject*>::iterator obj=objects.begin(); obj<objects.end(); ++obj){
		(*obj)->updateObject(screenOffsetX, screenOffsetY);
	}
}

