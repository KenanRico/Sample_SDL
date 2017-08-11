#include <iostream> //remove

#ifndef OBJECT_LAYER_OBJECT_H
#define OBJECT_LAYER_OBJECT_H
class ObjectLayerObject{
	public:
		enum contact{
			NONE = 0,
			TOP = 1,
			BOTTOM = 2,
			LEFT = 3,
			RIGHT = 4
		};
	protected:
		int ID;
		int x0;
		int y0;
		int x;
		int y;
	public:
		ObjectLayerObject() = delete;
		virtual ~ObjectLayerObject();
		ObjectLayerObject(const ObjectLayerObject&) = delete;
		ObjectLayerObject& operator=(const ObjectLayerObject&) = delete;
	public:
		ObjectLayerObject(int,int,int);
	public:
		void updateObject(int,int);
	public:
		virtual bool onContact(int,int,int,int,int) const = 0;
		virtual int top() const;
		virtual int bottom() const;
		virtual int left() const;
		virtual int right() const;
		virtual int angleLeft() const;
		virtual int angleRight() const;
		virtual void printInfo() const; //debug. remove
};
#endif


//probably a good idea to declare a collision handler class and have an instance of that in every ObjectLayerObject object
