#include <SDL2/SDL.h>
#include "game.h"

#ifdef main
#undef main
#endif


int main()
{
	Game::startGame();
//	testRun();
	return 0;
}



