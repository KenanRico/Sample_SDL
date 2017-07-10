#include <SDL2/SDL.h>
#include <map>
#include <string>
#include "menuitem.h"
#include "eventhandler.h"


#ifndef MENU_H
#define MENU_H
class Menu{
	private:
		SDL_Renderer* mainRendererPointer;
		SDL_Texture* background;
		std::map<std::string, MenuItem*> items;
	public:
		Menu() = delete;
		~Menu();
		Menu(const Menu&) = delete;
		Menu& operator=(const Menu&) = delete;
	public:
		Menu(SDL_Renderer*);
	public:
		void setBackground(const char*);
		bool addItem(const char*, MenuItem*);
		void renderMenu(SDL_Window*);
		void updateMenu(const EventHandler&);
		const MenuItem& operator[](const char*);
	private:
		void destroyItems();
		void clear();	
};
#endif
