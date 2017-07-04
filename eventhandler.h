#include <SDL2/SDL.h>
#include "keyboardhandler.h"
//#include "mousehandler.h"

#ifndef EVENT_HANDLER
#define EVENT_HANDLER
class EventHandler{
	private:
		bool quitgame;
	private:
		mutable	KeyboardHandler keyboard;
		//MouseHandler mouse;
	public:
		EventHandler();
		~EventHandler();
		EventHandler(const EventHandler&) = delete;
		EventHandler& operator=(const EventHandler&) = delete;
	public:	
		void parseEvent(SDL_Event&);
		bool quit() const;
		bool getKeyboard(int) const;
	private:
		void resetEscape();

};
#endif
