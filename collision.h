#include "sprite.h"
#include "objectlayerobject.h"
#include <vector>
#include <map>
#include <string>


#ifndef COLLISION_H
#define COLLISION_H
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
		Collision(const Sprite&);
		~Collision();
		Collision() = delete;
		Collision(const Collision&) = delete;
		Collision& operator=(const Collision&) = delete;
	public:
		static void updateCollidables(const std::map<std::string, Sprite*>&, const std::vector<ObjectLayerObject*>&);
	public:
		CollisionDetail getCollisionInfo(); //update and return collisionInfo
};
#endif
