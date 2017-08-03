#include "objectlayerobject.h"
#include <vector>


#ifndef OBJECT_LAYER_POLYLINE_H
#define OBJECT_LAYER_POLYLINE_H
class ObjectLayerPolyline : public ObjectLayerObject{
	private:
		struct point{int x; int y;};
	private:
		std::vector<point> points;
	public:
		ObjectLayerPolyline() = delete;
		~ObjectLayerPolyline();
		ObjectLayerPolyline(const ObjectLayerPolyline&) = delete;
		ObjectLayerPolyline& operator=(const ObjectLayerPolyline&) = delete;
	public:
		ObjectLayerPolyline(int,int,int);
	public:
		bool onContact(int,int,int,int,int) const override;
		void insertPoint(int,int);
};
#endif
