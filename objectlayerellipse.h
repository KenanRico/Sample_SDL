#include "objectlayerobject.h"


#ifndef OBJECT_LAYER_ELLIPSE_H
#define OBJECT_LAYER_ELLIPSE_H
class ObjectLayerEllipse : public ObjectLayerObject{
	private:
		int width;
		int height;
	public:
		ObjectLayerEllipse() = delete;
		~ObjectLayerEllipse();
		ObjectLayerEllipse(const ObjectLayerEllipse&) = delete;
		ObjectLayerEllipse& operator=(const ObjectLayerEllipse&) = delete;
	public:
		ObjectLayerEllipse(int,int,int,int,int);
	public:
		bool onContact() override;
};
#endif
