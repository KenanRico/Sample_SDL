#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#ifndef GAMESYSTEM_NAMESPACE
#define GAMESYSTEM_NAMESPACE
namespace GameSystem{
//-------------------------System parameters-----------------------------
	const int PixToMetre = 30;
	const int FPS = 60;
	const int FrameTime = 1000.0f/FPS;
	const int defaultWindowW = 640;
	const int defaultWindowH = 480;
//--------------------------SDL_Init-------------------------------------
	inline void Init(){
		try{
			if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
                		throw SDL_GetError();
	        	}else;
		}catch(const char* s){
			std::cerr<<s<<"\n";
		}
		std::cout<<"Init success! Init() \n";
	}
//---------------------------SDL_Quit---------------------------------------
	inline void Quit(){
		SDL_Quit();
		std::cout<<"Quit SDL! Quit() \n";
	}
//--------------------------SDL_Delay---------------------------------------
	inline void Pause(int ms){
		try{
			if(ms>=0){
				SDL_Delay(ms);	
			}else{
				throw -1;
			}
		}catch(int error){
			std::cerr<<"Time entered must be > 0 \n";;
		}
	}
//-------------------------Print Message-------------------------------------
	inline void writeErrorMessage(const char* err_msg){
		std::cerr<<"******Fatal Error: "<<err_msg<<"\n";;
	}

	inline void writeMessage(const char* msg){
		std::cout<<msg<<"\n";	
	}
//------------------------State Enum----------------------------------------

}
#endif 
