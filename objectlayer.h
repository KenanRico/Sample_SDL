#include <vector>
//#include "objectlayerobject.h"



#ifndef OBJECT_LAYER_H
#define OBJECT_LAYER_H
class ObjectLayer{
	private:
		//std::vector<ObjectLayerEllipse*> ellipses;
		//std::vector<ObjectLayerRectangle*> rectangles;
		//std::vector<ObjectLayerPolygon*> polygons;
		//std::vector<ObjectLayerPolyLine*> polylines;
		std::vector<ObjectLayerObject*> objects;
	public:
		ObjectLayer();
		~ObjectLayer();
		ObjectLayer(const ObjectLayer&) = delete;
		ObjectLayer& operator=(const ObjectLayer&) = delete;
	public:
		void insertObject(ObjectLayerObject*);
};
#endif
