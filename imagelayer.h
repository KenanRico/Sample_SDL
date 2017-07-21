#include <SDL2/SDL.h>
#include <string>



#ifndef IMAGE_LAYER_H
#define IMAGE_LAYER_H
class ImageLayer{
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
		ImageLayer() = delete;
		~ImageLayer();
		ImageLayer(const ImageLayer&) = delete;
		ImageLayer& operator=(const ImageLayer&) = delete;
	public:
		ImageLayer(const char*, const char*, int, int, int, int, SDL_Renderer*, SDL_Window*);
	private:
		void initImageLayer();
		void destroyImageLayer();
	public:
		void updateImageLayer(int,int) const;
		void renderImageLayer() const;
};
#endif
