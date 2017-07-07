#include <SDL2/SDL.h>
#include <string>
#include "eventhandler.h"


#ifndef MENU_ITEM_H
#define MENU_ITEM_H

class MenuItem(){
	protected:
		SDL_Renderer* m_mainRendererPointer;
		std::string m_sourceImage;
		SDL_Texture* m_texture;
		int m_imageW;
		int m_imageH;
		bool m_created;
		bool m_triggered;
	protected:
		SDL_Rect* m_srcRect;
		SDL_Rect* m_dstRect;
		
	public: 
		MenuItem() = delete;
		virtual ~MenuItem();
		MenuItem(const MenuItem&) = delete;
		MenuItem& operator=(const MenuItem&) = delete;
	public:
		MenuItem(SDL_Renderer*, const char*, int,int,int,int, int,int,int,int);
	private:
		void destroyItem();
		void createItem();

	public:
		virtual void render() = 0;
		virtual void onEvent(const EventHandler&) = 0;
		bool triggered() final;
	private:
};
#endif







