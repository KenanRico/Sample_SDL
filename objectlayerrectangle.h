#include "objectlayerobject.h"


#ifndef OBJECT_LAYER_RECTANGLE_H
#define OBJECT_LAYER_RECTANGLE_H
class ObjectLayerRectangle : public ObjectLayerObject{
	private:
		int width;
		int height;
	public:
		ObjectLayerRectangle() = delete;
		~ObjectLayerRectangle();
		ObjectLayerRectangle(const ObjectLayerRectangle&) = delete;
		ObjectLayerRectangle& operator=(const ObjectLayerRectangle&) = delete;
	public:
		ObjectLayerRectangle(int,int,int,int,int);
	public:
		bool onContact(int,int,int,int,int) const override;
		int top() const override;
		int bottom() const override;
		int left() const override;
		int right() const override;
	private:
		bool above(int,int,int,int) const;
		bool below(int,int,int,int) const;
		bool leftof(int,int,int,int) const;
		bool rightof(int,int,int,int) const;
};
#endif
