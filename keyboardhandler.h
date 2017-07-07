#include <SDL2/SDL.h>



#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H
class KeyboardHandler{
	private:
		bool* keys_pressed;
	public:
		enum Key{A=0,S=1,D=2,W=3,J=4,K=5,L=6,CTRL=7,ESCAPE=8};
	public: 
		KeyboardHandler();
		~KeyboardHandler();
		KeyboardHandler(const KeyboardHandler&) = delete;
		KeyboardHandler& operator=(const KeyboardHandler&) = delete;
	public:
		bool& set(int);
		bool operator[](int) const;
};
#endif
