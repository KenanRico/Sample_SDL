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
		GameSystem::writeErrorMessage("Object Manger already exists!");
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
	for(std::map<std::string, Sprite*>::iterator iter = o_Objects.begin(); iter!=o_Objects.end(); ++iter){
		delete iter->second;
	}
}


bool SpriteManager::insert(const char* ID, Sprite* sp_ptr){
	bool successful = false;
	if(o_Objects.find(ID)==o_Objects.end()){
		o_Objects[ID] = sp_ptr;
		o_Objects[ID]->createSprite();
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
	if(o_Objects.find(ID)!=o_Objects.end()){
		delete o_Objects[ID];
		o_Objects.erase(ID);
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
	if(o_Objects.find(ID)!=o_Objects.end()){
		return o_Objects[ID];
	}else{
		std::string Err1 = "Cannot find object. Object ID ";
		std::string Err2 = " does not exist";
		std::string Err = Err1 + std::string(ID) + Err2;
		GameSystem::writeErrorMessage(Err.c_str());
		return (Sprite*)0;
	}	
}

unsigned int SpriteManager::count(){
	return o_Objects.size();
}
