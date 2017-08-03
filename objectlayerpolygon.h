#include "objectlayerobject.h"
#include <vector>

#ifndef OBJECT_LAYER_POLYGON_H
#define OBJECT_LAYER_POLYGON_H
class ObjectLayerPolygon : public ObjectLayerObject{
	private:
		struct point{int x; int y;};
	private:
		std::vector<point> points;
	public:
		ObjectLayerPolygon() = delete;
		~ObjectLayerPolygon();
		ObjectLayerPolygon(const ObjectLayerPolygon&) = delete;
		ObjectLayerPolygon& operator=(const ObjectLayerPolygon&) = delete;
	public:
		ObjectLayerPolygon(int,int,int);
	public:
		bool onContact(int,int,int,int,int) const override;
		void insertPoint(int,int);
};
#endif
