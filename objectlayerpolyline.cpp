#include "objectlayerobject.h"
#include "objectlayerpolyline.h"

ObjectLayerPolyline::ObjectLayerPolyline(int _id, int _x, int _y):
ObjectLayerObject(_id, _x, _y){
	;
}

ObjectLayerPolyline::~ObjectLayerPolyline(){
	;
}


bool ObjectLayerPolyline::onContact(){

}

void ObjectLayerPolyline::insertPoint(int x, int y){
	points.push_back((point){x,y});
}
