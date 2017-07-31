

#ifndef OBJECT_LAYER_OBJECT_H
#define OBJECT_LAYER_OBJECT_H
class ObjectLayerObject{
	public:
		enum contact{
			NONE = 0,
			TOP = 1,
			BOTTOM = 2,
			LEFT = 3,
			RIGHT = 4;
		}
	protected:
		int ID;
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
		virtual bool onContact(int,int,int) = 0;
	protected:
		virtual bool above(int,int,int,int) = 0;
		virtual bool below(int,int,int,int) = 0;
		virtual bool leftof(int,int,int,int) = 0;
		virtual bool rightof(int,int,int,int) = 0;
};
#endif


//probably a good idea to declare a collision handler class and have an instance of that in every ObjectLayerObject object
