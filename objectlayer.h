#include <string>
#include <vector>
#include "objectlayerobject.h"


#ifndef OBJECT_LAYER_H
#define OBJECT_LAYER_H
class ObjectLayer{
	private:
		std::string name;
	private:
		std::vector<ObjectLayerObject*> objects;
	public:
		ObjectLayer(const char*);
		~ObjectLayer();
		ObjectLayer(const ObjectLayer&) = delete;
		ObjectLayer& operator=(const ObjectLayer&) = delete;
	public:
		void insertObject(ObjectLayerObject*);
		const std::vector<ObjectLayerObject*>& getObjects() const;
		void updateObjectLayer(int,int);
};
#endif
