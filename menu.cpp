#include <SDL2/SDL.h>
#include <SDL2/extensions/SDL_image.h>
#include "gamesystem.h"
#include "menu.h"
#include "menuitem.h"
#include <map>


Menu::Menu(SDL_Renderer* g_renderer): mainRendererPointer(g_renderer), background((SDL_Texture*)0){
	;
}

Menu::~Menu(){
	destroyItems();
	clear();
}


void Menu::setBackground(const char* img_path){
	SDL_Surface* temp_surf = IMG_Load(img_path);
	background = SDL_CreateTextureFromSurface(mainRendererPointer, temp_surf);
	SDL_FreeSurface(temp_surf);
}

bool Menu::addItem(const char* name, MenuItem* new_item){
	bool success = false;
	if(items.find(name)==items.end()){
		items[name] = new_item;
		success = true;
	}else{
		std::string Err1 = "Failed to insert MenuItem. Item ID ";
		std::string Err2 = " already exists";
		std::string Err = Err1 + std::string(name) + Err2;
		GameSystem::writeErrorMessage(Err.c_str());
	}
	return success;
}

void Menu::renderMenu(SDL_Window* window){
	SDL_RenderClear(mainRendererPointer);
	GameSystem::writeMessage("Rendering Menu");
	SDL_Rect srcRect{0,0,0,0};
	SDL_QueryTexture(background, 0, 0, &srcRect.w, &srcRect.h);
	SDL_Rect dstRect{0,0,0,0};
	SDL_GetWindowSize(window, &dstRect.w, &dstRect.h);
	SDL_RenderCopy(mainRendererPointer, background, &srcRect, &dstRect);
	for(std::map<std::string, MenuItem*>::iterator iter=items.begin(); iter!=items.end(); ++iter){
		iter->second->render();
	}
	SDL_RenderPresent(mainRendererPointer);
}

void Menu::updateMenu(const EventHandler& event){
	for(std::map<std::string, MenuItem*>::iterator iter=items.begin(); iter!=items.end(); ++iter){
		iter->second->onEvent(event);
	}
}

const MenuItem& Menu::operator[](const char* name){
	return *items[name];
}

void Menu::destroyItems(){
	SDL_DestroyTexture(background);
	for(std::map<std::string, MenuItem*>::iterator iter=items.begin(); iter!=items.end(); ++iter){
		delete iter->second;
	}
}
void Menu::clear(){
	SDL_RenderClear(mainRendererPointer);
}

