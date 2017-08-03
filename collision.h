#include "objectlayerobject.h"
#include "objectlayer.h"
#include <vector>
#include <map>
#include <string>
//#include "sprite.h"

#ifndef COLLISION_H
#define COLLISION_H
class Sprite;
class Collision{
	public:
		struct CollisionDetail{
			bool top;
			bool bottom;
			bool left;
			bool right;
			int angle_right;
			int angle_left;
		};

	private:
		const Sprite* mySprite;
		CollisionDetail collisionInfo;
	private:	
		static std::vector<Sprite*> sprites;
		static std::vector<ObjectLayerObject*> objects;
	public:
		Collision(const Sprite*);
		~Collision();
		Collision() = delete;
		Collision(const Collision&) = delete;
		Collision& operator=(const Collision&) = delete;
	public:
		static void updateCollidables(const std::map<std::string, Sprite*>&, const std::vector<ObjectLayer*>&);
	public:
		void updateCollisionInfo();
		CollisionDetail getCollisionInfo(); //update and return collisionInfo
};
#endif
