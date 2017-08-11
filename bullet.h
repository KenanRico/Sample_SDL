#include <SDL2/SDL.h>


#ifndef BULLET_H
#define BULLET_H
class Bullet{
	private:
		int direction;
		int speedX;
		int speedY;
		bool flying;
		int startingFrame;
		const unsigned int* frameCounter;
	private:
		SDL_Renderer* mainRendererPointer;
		SDL_Texture* texture;
		SDL_Rect* srcRect;
		SDL_Rect* dstRect;
	public:
		Bullet(const char*,int,int,int,int,int,const unsigned int*, SDL_Renderer*);
		~Bullet();
		Bullet() = delete;
		Bullet(const Bullet&) = delete;
		Bullet& operator=(const Bullet&) = delete;
	private:
		void createBullet(const char*);
		void destroyBullet();
	public:
		void updateState();
		void updateSprite();
		void render();
		bool isFlying() const;
};
#endif
