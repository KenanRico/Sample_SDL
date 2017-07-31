#include "objectlayer.h"
#include <vector>



ObjectLayer::ObjectLayer(){;}

ObjectLayer::~ObjectLayer(){
	for(std::vector<ObjectLayerObject*>::iterator i=objects.begin(); i<objects.end(); ++i){
		delete *i;
	}
}


void ObjectLayer::insertObject(ObjectLayerObject* obj){
	objects.push_back(obj);
}
