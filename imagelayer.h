#include <SDL2/SDL.h>
#include <string>



#ifndef IMAGE_LEVEL_H
#define IMAGE_LEVEL_H
class ImageLevel{
	private:
		std::string name;
		std::string source;
		int width;
		int height;
		int offsetx;
		int offsety;
		SDL_Renderer* mainRendererPointer;
		SDL_Window* mainWindowPointer;
		SDL_Texture* texture;
		SDL_Rect* srcRect;
		SDL_Rect* dstRect;
	public:
		ImageLevel() = delete;
		~ImageLevel();
		ImageLevel(const ImageLevel&) = delete;
		ImageLevel& operator=(const ImageLevel&) = delete;
	public:
		ImageLevel(const char*, const char*, int, int, int, int, SDL_Renderer*, SDL_Window*);
	private:
		void initImageLayer();
		void destroyImageLayer();
	public:
		void updateImageLayer();
		void renderImageLayer();
};
#endif
