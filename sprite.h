#include <SDL2/SDL.h>
#include <string>


#ifndef SPRITE_H
#define SPRITE_H
class Sprite{
	private: 
		std::string s_sourceImage;
		SDL_Texture* s_texture;
		int s_imageW;
		int s_imageH;
		SDL_Rect s_srcRect;
		SDL_Rect s_dstRect;
	public:
		Sprite() = delete;
		~Sprite();
		Sprite(const Sprite&);
		Sprite& operator=(const Sprite&) = delete;
	public:
		Sprite(const char*);
		SDL_Rect getSourceRectangle();
		SDL_Rect getDestinationRectangle();
	private:
		void createSprite();
		void destroySprite();
};
#endif
