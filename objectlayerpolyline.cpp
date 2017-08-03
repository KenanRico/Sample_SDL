#include "objectlayerobject.h"
#include "objectlayerpolyline.h"

ObjectLayerPolyline::ObjectLayerPolyline(int _id, int _x, int _y):
ObjectLayerObject(_id, _x, _y){
	;
}

ObjectLayerPolyline::~ObjectLayerPolyline(){
	;
}


bool ObjectLayerPolyline::onContact(int side, int y1, int y2, int x1, int x2) const{
	return false;
}

void ObjectLayerPolyline::insertPoint(int x, int y){
	points.push_back((point){x,y});
}
