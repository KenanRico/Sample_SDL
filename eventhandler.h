#include <SDL2/SDL.h>
#include "keyboardhandler.h"
#include "mousehandler.h"

#ifndef EVENT_HANDLER
#define EVENT_HANDLER
class EventHandler{
	private:
		bool quitgame;
	private:
		mutable	KeyboardHandler keyboard;
		mutable MouseHandler mouse;	
		//MouseHandler mouse;
	public:
		EventHandler();
		~EventHandler();
		EventHandler(const EventHandler&) = delete;
		EventHandler& operator=(const EventHandler&) = delete;
	public:	
		void parseEvent();
		bool quit() const;
		const KeyboardHandler& getKeyboard() const;
		const MouseHandler& getMouse() const;
	private:
		void resetEscape();

};
#endif
