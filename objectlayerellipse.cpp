#include "objectlayerobject.h"
#include "objectlayerellipse.h"


ObjectLayerEllipse::ObjectLayerEllipse(int _id, int _x, int _y, int _w, int _h):
ObjectLayerObject(_id, _x, _y),
width(_w), height(_h){
	;
}

ObjectLayerEllipse::~ObjectLayerEllipse(){;}


bool ObjectLayerEllipse::onContact(int side, int y1, int y2, int x1, int x2) const{
	return false;
}
