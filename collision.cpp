#include "collision.h"
#include "sprite.h"
#include "objectlayerobject.h"
#include <vector>
#include <map>
#include <string>

Collision::Collision(const Sprite& s): mySprite(&s), collisionDetail((Contacts){false,false,false,false,0,0}){;}

Collision::~Collision(){;}


void Collision::updateCollidables(const std::map<std::string, Sprite*>& spriteMap, const std::vector<ObjectLayerObject*>& objectVec){
	sprites.clear();
	objects.clear();
	for(std::map<std::string, Sprite*>::iterator i=spriteMap.begin(); i!=spriteMap.end(); ++i){
		sprites.push(*i);
	}
	std::vector<Sprite*>::iterator iter = mySprite;
	sprites.erase(iter);
	for(std::vector<ObjectLayerObject*>::const_iterator i=objectVec.begin(); i<objectVec.end(); ++i){
		objects.push(*i);
	}
}


CollisionDetail Collision::getCollisionInfo(){
	collisionInfo.top = false;
	collisionInfo.bottom = false;
	collisionInfo.left = false;
	collisionInfo.right = false;
	collisionInfo.angle_left = 0;
	collisionInfo.angle_right = 0;	

	for(std::vector<Sprite*>::const_iterator iter=sprites.begin(); iter<sprites.end(); ++iter){
		const Sprite* target = *iter;
		//top collision check
		if(!collisionInfo.top){
			if(mySprite->getBottom() > target->getBottom()){
				if(mySprite->getTop() - target->getBottom() <= 1){
					collisionInfo.top = true;
				}else;
			}else;
		}else;
		//bottom collision check
		if(!collisionInfo.bottom){
			if(mySprite->getTop() < target->getTop()){
				if(target->getTop() - mySprite->getBottom() <= 1){
					collisionInfo.bottom = true;
				}else;
			}else;
		}else;
		//left collision check
		if(!collisionInfo.left){
			if(mySprite->getLeft() < target->getLeft()){
				if(target->getLeft() - mySprite->getRight() <= 1){
					collisionInfo.left = true;
				}else;
			}else;
		}else;
		//right collision check
		if(!collisionInfo.right){
			if(mySprite->getRight() > target->getRight()){
				if(mySprite->getLeft() - target->getRight() <= 1){
					collisionInfo.right = true;
				}else;
			}else;
		}else;
	}
	for(std::vector<ObjectLayerObject*>::const_iterator iter=objects.begin(); iter<objects.end(); ++iter){
		const ObjectLayerObject* target = *iter;
		if(!collisionInfo.top){
			collisionInfo.top = target->onContact(ObjectLayerObject::TOP, mySprite->getTop(), mySprite->getBottom());
		}else;
		if(!collisionInfo.bottom){
			collisionInfo.bottom = target->onContact(ObjectLayerObject::BOTTOM, mySprite->getTop(), mySprite->getBottom());
		}else;
		if(!collisionInfo.left){
			if(target->onContact(ObjectLayerObject::LEFT, mySprite->getLeft(), mySprite->getRight())){
				collisionInfo.left = true;
				collisionInfo.angle_left = target->angleLeft(/*arguments*/);
			}else;
		}else;
		if(!collisionInfo.right){
			if(target->onContact(ObjectLayerObject::RIGHT, mySprite->getLeft(), mySprite->getRight())){
				collisionInfo.right = true;
				collisionInfo.angle_right = target->angleRight(/*arguments*/);
			}else;
		}else;
	}
	return collisionInfo;
}

