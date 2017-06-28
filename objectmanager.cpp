#include "objectmanager.h"
#include "sprite.h"
#include "gamesystem.h"
#include <map>
#include <string>


bool ObjectManager::Exist = false;

ObjectManager* ObjectManager::Init(){
	if(!ObjectManager::Exist){
		ObjectManager::Exist = true;
		return new ObjectManager;
	}else{
		GameSystem::writeErrorMessage("Object Manger already exists!");
		return (ObjectManager*)0;
	}
}

ObjectManager::ObjectManager(){
	;
} 
ObjectManager::~ObjectManager(){
	freeObjects();
}

void ObjectManager::freeObjects(){
	//delete all Sprite* in "Objects"
	for(std::map<std::string, Sprite*>::iterator iter = o_Objects.begin(); iter!=o_Objects.end(); ++iter){
		delete iter->second;
	}
}


bool ObjectManager::insert(const char* ID, Sprite* sp_ptr){
	bool successful = false;
	if(o_Objects.find(ID)!=o_Objects.end()){
		o_Objects[ID] = sp_ptr;
		successful = true;
	}else{
		std::string Err1 = "Failed to insert object. Object ID ";
		std::string Err2 = " already exists";
		std::string Err = Err1 + std::string(ID) + Err2;
		GameSystem::writeErrorMessage(Err.c_str());
	}	
	return successful;
}

bool ObjectManager::remove(const char* ID){
	bool successful = false;
	if(o_Objects.find(ID)!=o_Objects.end()){
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

Sprite* ObjectManager::get(const char* ID){
	return o_Objects[ID];
}

unsigned int ObjectManager::count(){
	return o_Objects.size();
}
