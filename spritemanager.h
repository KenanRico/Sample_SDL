#include "sprite.h"
#include <map>
#include <string>




#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H
class SpriteManager{
	public: static SpriteManager* Init();
	private: static bool Exist;

	private:
		std::map<std::string, Sprite*> o_sprites;

	private:
		SpriteManager();
	public:
		~SpriteManager();
		SpriteManager(const SpriteManager&) = delete;
		SpriteManager& operator=(const SpriteManager&) = delete;
	private: 
		void freeObjects();
	
	public:
		bool insert(const char*, Sprite*);
		bool remove(const char*);
		Sprite* get(const char*);
		unsigned int count();
	public:
		void updateAllStates(const EventHandler&);
		void updateAllSprites();
		void renderAllSprites();

};
#endif
