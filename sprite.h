#include <SDL2/SDL.h>
#include <string>
#include "eventhandler.h"


#ifndef SPRITE_H
#define SPRITE_H
class Sprite{
	protected:
		SDL_Renderer** s_mainRendererPointer;
		std::string s_sourceImage;
		SDL_Texture* s_texture;
		int s_imageW;
		int s_imageH;
		bool s_created;
		unsigned int s_framecounter;
	protected:
		SDL_Rect* s_srcRect;
		SDL_Rect* s_dstRect;

	public:
		Sprite() = delete;
		virtual ~Sprite();
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;
	public:
		void createSprite();

		Sprite(SDL_Renderer*&, const char*, int, int, int, int, int, int, int, int);

		//void moveRight(); //Will move to inherited classes
		virtual void updateState(const EventHandler&) = 0;//to be implemented by each derived based on there own states
		virtual void updateSprite() = 0;
		virtual void renderSprite() = 0;
	protected:
		void setSrcRect(int,int,int,int);
		void setDstRect(int,int,int,int);
		void resetFrameCounter();		
		
	private:
		void destroySprite();


};
#endif
