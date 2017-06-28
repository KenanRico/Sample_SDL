#include <SDL2/SDL.h>
#include <string>

#ifndef SPRITE_H
#define SPRITE_H
class Sprite{
	private:
		SDL_Renderer** s_mainRendererPointer;
		std::string s_sourceImage;
		SDL_Texture* s_texture;
		int s_imageW;
		int s_imageH;
		SDL_Rect* s_srcRect;
		SDL_Rect* s_dstRect;
		bool s_created;
	public:
		Sprite() = delete;
		~Sprite();
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;
	public:
		void createSprite();

		Sprite(SDL_Renderer*&, const char*, int, int, int, int, int, int, int, int);
		SDL_Texture* getTexturePtr();
		SDL_Rect* getSrcRectPtr();
		SDL_Rect* getDstRectPtr();

		void setSrcRect(int,int,int,int);
		void setDstRect(int,int,int,int);

		void moveRight(); //might move to inherited classes
	private:
		void destroySprite();


};
#endif
