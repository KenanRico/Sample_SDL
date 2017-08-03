#include "objectlayerobject.h"
#include "objectlayerpolygon.h"

ObjectLayerPolygon::ObjectLayerPolygon(int _id, int _x, int _y):
ObjectLayerObject(_id, _x, _y){
	;
}

ObjectLayerPolygon::~ObjectLayerPolygon(){;}


bool ObjectLayerPolygon::onContact(int side, int y1, int y2, int x1, int x2) const{
	return false;
}

void ObjectLayerPolygon::insertPoint(int x, int y){
	points.push_back((point){x,y});
}


