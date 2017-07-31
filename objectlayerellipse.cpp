#include "objectlayerobject.h"
#include "objectlayerellipse.h"


ObjectLayerEllipse::ObjectLayerEllipse(int _id, int _x, int _y, int _w, int _h):
ObjectLayerObject(_id, _x, _y),
width(_w), height(_h){
	;
}

ObjectLayerEllipse::~ObjectLayerEllipse(){;}


bool ObjectLayerEllipse::onContact() override{

}
