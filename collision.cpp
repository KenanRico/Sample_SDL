#include "collision.h"
#include "objectlayerobject.h"
#include <vector>
#include <map>
#include <string>
#include "sprite.h"



Collision::Collision(const Sprite* sp): mySprite(sp), collisionInfo((CollisionDetail){false,0,false,0,false,0,false,0, 0,0}){;}

Collision::~Collision(){;}

std::vector<Sprite*> Collision::sprites;
std::vector<ObjectLayerObject*> Collision::objects;
void Collision::updateCollidables(const std::map<std::string, Sprite*>& spriteMap, const std::vector<ObjectLayer*>& objectLayerVec){
	sprites.clear();
	objects.clear();
	for(std::map<std::string, Sprite*>::const_iterator i=spriteMap.begin(); i!=spriteMap.end(); ++i){
		sprites.push_back(i->second);
	}
	for(std::vector<ObjectLayer*>::const_iterator i=objectLayerVec.begin(); i<objectLayerVec.end(); ++i){
		const std::vector<ObjectLayerObject*>& objectVec = (*i)->getObjects();
		for(std::vector<ObjectLayerObject*>::const_iterator j=objectVec.begin(); j<objectVec.end(); ++j){
			objects.push_back(*j);
			(*j)->printInfo();
		}
	}
}


void Collision::updateCollisionInfo(){
	collisionInfo.top = false;
	collisionInfo.lowesttop = 0;
	collisionInfo.bottom = false;
	collisionInfo.highestbottom = 3000;
	collisionInfo.left = false;
	collisionInfo.rightmostleft = 0;
	collisionInfo.right = false;
	collisionInfo.leftmostright = 3000;
	collisionInfo.angle_left = 0;
	collisionInfo.angle_right = 0;	
	int top = mySprite->getTop();
	int bottom = mySprite->getBottom();
	int left = mySprite->getLeft();
	int right = mySprite->getRight();
	for(std::vector<Sprite*>::const_iterator iter=sprites.begin(); iter<sprites.end(); ++iter){
		if(mySprite->getName()!=(*iter)->getName()){
			const Sprite* target = *iter;
			//top collision check
			if(!collisionInfo.top){
				if(bottom > target->getBottom()){
					if(top - target->getBottom() <= 1){
						collisionInfo.top = true;
					}else;
				}else;
			}else;
			//bottom collision check
			if(!collisionInfo.bottom){
			if(top < target->getTop()){
				if(target->getTop() - bottom <= 1){
						collisionInfo.bottom = true;
					}else;
				}else;
			}else;
			//left collision check
			if(!collisionInfo.left){
				if(left < target->getLeft()){
					if(target->getLeft() - right <= 1){
						collisionInfo.left = true;
					}else;
				}else;
			}else;
			//right collision check
			if(!collisionInfo.right){
				if(right > target->getRight()){
					if(right - target->getRight() <= 1){
						collisionInfo.right = true;
					}else;
				}else;
			}else;
		}
	}
	for(std::vector<ObjectLayerObject*>::const_iterator iter=objects.begin(); iter<objects.end(); ++iter){
		const ObjectLayerObject* target = *iter;	
		if(!collisionInfo.top){
			collisionInfo.top = target->onContact(ObjectLayerObject::TOP, top, bottom, left, right);
			if(collisionInfo.top){
				if(target->bottom() > collisionInfo.lowesttop){
					collisionInfo.lowesttop = target->bottom();
				}else;
			}else;
		}else;
		if(!collisionInfo.bottom){
			collisionInfo.bottom = target->onContact(ObjectLayerObject::BOTTOM, top, bottom, left, right);
			if(collisionInfo.bottom){
				if(target->top() < collisionInfo.highestbottom){
					collisionInfo.highestbottom = target->top();
				}else;
			}else;
		}else;
		if(!collisionInfo.left){
			//if(target->onContact(ObjectLayerObject::LEFT, top, bottom, left, right)){
			collisionInfo.left = target->onContact(ObjectLayerObject::LEFT, top, bottom, left, right);
			if(collisionInfo.left){
				if(target->right() > collisionInfo.rightmostleft){
					collisionInfo.rightmostleft = target->right();
				}else;
			}else;
			collisionInfo.angle_left = target->angleRight(/*arguments*/);
			//}else;
		}else;
		if(!collisionInfo.right){
			//if(target->onContact(ObjectLayerObject::RIGHT, top, bottom, left, right)){
				//collisionInfo.right = true;
			collisionInfo.right = target->onContact(ObjectLayerObject::RIGHT, top, bottom, left, right);
			if(collisionInfo.right){
				if(target->left() < collisionInfo.leftmostright){
					collisionInfo.leftmostright = target->left();
				}else;
			}else;
			collisionInfo.angle_right = target->angleLeft(/*arguments*/);
			//}else;
		}else;
	}
}

Collision::CollisionDetail Collision::getCollisionInfo(){
	return collisionInfo;
}
