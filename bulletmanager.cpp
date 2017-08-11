#include "bulletmanager.h"
#include <vector>
#include "bullet.h"


BulletManager::BulletManager(){;}
BulletManager::~BulletManager(){
	for(std::vector<Bullet*>::iterator b=bullets.begin(); b<bullets.end(); ++b){
		delete *b;
	}
}

void BulletManager::shoot(Bullet* bullet){
	if(bullets.size()<=150){
		bullets.push_back(bullet);
	}else;
}

void BulletManager::update(){
	for(std::vector<Bullet*>::iterator b=bullets.begin(); b<bullets.end(); ++b){
		if((*b)->isFlying()){
			(*b)->updateState();
			(*b)->updateSprite();
		}else{
			delete *b;
			bullets.erase(b);
		}
	}
}

void BulletManager::renderAllBullets(){
	for(std::vector<Bullet*>::iterator b=bullets.begin(); b<bullets.end(); ++b){
		(*b)->render();
	}
}
