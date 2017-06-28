#include "sprite.h"
#include <map>
#include <string>




#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H
class ObjectManager{
	public: static ObjectManager* Init();
	private: static bool Exist;

	private:
		std::map<std::string, Sprite*> o_Objects;

	private:
		ObjectManager();
	public:
		~ObjectManager();
		ObjectManager(const ObjectManager&) = delete;
		ObjectManager& operator=(const ObjectManager&) = delete;
	private: 
		void freeObjects();
	
	public:
		bool insert(const char*, Sprite*);
		bool remove(const char*);
		Sprite* get(const char*);
		unsigned int count();

};
#endif
