#include <SDL2/SDL.h>
#include "menuitem.h"
#include "gamesystem.h"


MenuItem::MenuItem(SDL_Renderer* g_renderer, const char* path, int sx,int sy,int sw,int sh, int dx,int dy,int dw,int dh):
m_mainRendererPointer(g_renderer),
m_sourceImage(path),
m_srcRect(new SDL_Rect{sx,sy,sw,sh}),
m_dstRect(new SDL_Rect{dx,dy,dw,dh}),
m_imageW(0),
m_imageH(0),
m_created(false),
m_triggered(false){
	createItem();
}

MenuItem::~MenuItem(){
	destroyItem();
}

void MenuItem::createItem(){
	if(m_created){
		std::string Err1("Already created menu item with image: ");
		std::string Err = Err1+m_sourceImage;
		GameSystem::writeErrorMessage(Err.c_str());
		return;
	}else;
	SDL_Surface* temp_surf = IMG_Load(m_sourceImage.c_str());
	if(*temp_surf!=(SDL_Surface*)0){
		s_texture = SDL_CreateTextureFromSurface(*m_mainRendererPointer, temp_surf);
	}else{
		std::string Err1("Failed to load image: ");
		std::string Err = Err1+s_sourceImage;
		GameSystem::writeErrorMessage(Err.c_str());
	}
	SDL_FreeSurface(temp_surf);
	if(*m_texture!=(SDL_Texture*0)){
		SDL_QueryTexture(s_texture, 0, 0, &m_imageW, &m_imageH);	
	}else;
	m_created = true;	
	GameSystem::writeMessage("Created MenuItem");
}

void MenuItem::destroyItem(){
	SDL_DestroyTexture(m_texture);
	delete m_srcRect;
	delete m_dstRect;
	GameSystem::writeMessage("Created MenuItem");
}

bool MenuItem::triggered(){
	return m_triggered;
}

