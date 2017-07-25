#include "spritemanager.h"
#include "sprite.h"
#include "gamesystem.h"
#include <map>
#include <string>


bool SpriteManager::Exist = false;

SpriteManager* SpriteManager::Init(){
	if(!SpriteManager::Exist){
		SpriteManager::Exist = true;
		return new SpriteManager;
	}else{
		GameSystem::writeErrorMessage("Object Manager already exists!");
		return (SpriteManager*)0;
	}
}

SpriteManager::SpriteManager(){
	;
} 
SpriteManager::~SpriteManager(){
	freeObjects();
}

void SpriteManager::freeObjects(){
	//delete all Sprite* in "Objects"
	for(std::map<std::string, Sprite*>::iterator iter = o_sprites.begin(); iter!=o_sprites.end(); ++iter){
		delete iter->second;
	}
}


bool SpriteManager::insert(const char* ID, Sprite* sp_ptr){
	bool successful = false;
	if(o_sprites.find(ID)==o_sprites.end()){
		o_sprites[ID] = sp_ptr;
		o_sprites[ID]->createSprite();
		successful = true;
	}else{
		std::string Err1 = "Failed to insert object. Object ID ";
		std::string Err2 = " already exists";
		std::string Err = Err1 + std::string(ID) + Err2;
		GameSystem::writeErrorMessage(Err.c_str());
	}	
	return successful;
}

bool SpriteManager::remove(const char* ID){
	bool successful = false;
	if(o_sprites.find(ID)!=o_sprites.end()){
		delete o_sprites[ID];
		o_sprites.erase(ID);
		successful = true;
	}else{
		std::string Err1 = "Failed to remove object. Object ID ";
		std::string Err2 = " does not exist";
		std::string Err = Err1 + std::string(ID) + Err2;
		GameSystem::writeErrorMessage(Err.c_str());
	}
	return successful;
}

Sprite* SpriteManager::get(const char* ID){
	if(o_sprites.find(ID)!=o_sprites.end()){
		return o_sprites[ID];
	}else{
		std::string Err1 = "Cannot find object. Object ID ";
		std::string Err2 = " does not exist";
		std::string Err = Err1 + std::string(ID) + Err2;
		GameSystem::writeErrorMessage(Err.c_str());
		return (Sprite*)0;
	}	
}

unsigned int SpriteManager::count(){
	return o_sprites.size();
}


void SpriteManager::updateAllStates(const EventHandler& event){
	for(std::map<std::string, Sprite*>::iterator i=o_sprites.begin(); i!=o_sprites.end(); ++i){
		i->second->updateState(event);
	}
}
void SpriteManager::updateAllSprites(){
	for(std::map<std::string, Sprite*>::iterator i=o_sprites.begin(); i!=o_sprites.end(); ++i){
		i->second->updateSprite();
	}
}
void SpriteManager::renderAllSprites(){
	for(std::map<std::string, Sprite*>::iterator i=o_sprites.begin(); i!=o_sprites.end(); ++i){
		i->second->renderSprite();
	}
}
