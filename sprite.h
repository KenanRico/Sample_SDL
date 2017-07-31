#include <SDL2/SDL.h>
#include <string>
#include "eventhandler.h"


#ifndef SPRITE_H
#define SPRITE_H
class Sprite{
	protected:
		SDL_Renderer* s_mainRendererPointer;
		std::string s_sourceImage;
		SDL_Texture* s_texture;
	protected:
		SDL_Rect* s_srcRect;
		SDL_Rect* s_dstRect;
	protected:
		int s_imageW;
		int s_imageH;
		int s_offsetX;
		int s_offsetY;
		bool s_created;
		unsigned int s_framecounter;

	public:
		Sprite() = delete;
		virtual ~Sprite();
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;
	public:
		virtual void createSprite() final;
		Sprite(SDL_Renderer*, const char*, int, int, int, int, int, int, int, int);

		//void moveRight(); //Will move to inherited classes
		virtual void updateState(const EventHandler&) = 0;//to be implemented by each derived based on there own states
		virtual void updateSprite() = 0;
		virtual void renderSprite() = 0;
	public:
		int getOffsetX() const;
		int getOffsetY() const;
	public:
		int getLeft() const;
		int getRight() const;
		int getTop() const;
		int getBottom() const;
	protected:
		void setSrcRect(int,int,int,int);
		void setDstRect(int,int,int,int);
		void resetFrameCounter();

	private:
		void destroySprite();


};
#endif
