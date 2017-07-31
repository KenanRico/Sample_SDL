#include "objectlayerobject.h"
#include "objectlayerpolygon.h"

ObjectLayerPolygon::ObjectLayerPolygon(int _id, int _x, int _y):
ObjectLayerObject(_id, _x, _y){
	;
}

ObjectLayerPolygon::~ObjectLayerPolygon(){;}


bool ObjectLayerPolygon::onContact(){


}

void ObjectLayerPolygon::insertPoint(int x, int y){
	points.push_back((point){x,y});
}


