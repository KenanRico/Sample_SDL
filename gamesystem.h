#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#ifndef GAMESYSTEM_NAMESPACE
#define GAMESYSTEM_NAMESPACE
namespace GameSystem{	
//--------------------------SDL_Init-------------------------------------
	inline void Init(){
		try{
			if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
                		throw SDL_GetError();
	        	}else;
		}catch(const char* s){
			std::cerr<<s<<std::endl;
		}
		std::cout<<"Init success! Init()"<<std::endl;
	}
//---------------------------SDL_Quit---------------------------------------
	inline void Quit(){
		SDL_Quit();
		std::cout<<"Quit SDL! Quit()"<<std::endl;
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
			std::cerr<<"Time entered must be > 0"<<std::endl;
		}
	}
//-------------------------Print Message-------------------------------------
	inline void writeErrorMessage(const char* err_msg){
		std::cerr<<"******Fatal Error: "<<err_msg<<std::endl;
	}

	inline void writeMessage(const char* msg){
		std::cout<<msg<<std::endl;	
	}
//------------------------State Enum----------------------------------------

}
#endif 
