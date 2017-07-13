



#ifndef OBJECT_CREATOR_H
#define OBJECT_CREATOR_H
class ObjectCreator{
	



};
#endif












template<typename T>
T* ObjectCreator::object(SDL_Renderer* g_renderer, std::stringstream& ss, const char* type){
	if(strcmp(type, "button")==0){
		int srcRectX = 0;
		int srcRectY = 0;
		int srcRectW = 0;
		int srcRectH = 0;


	}else if(strcmp(type, "player")==0){


	}else{
		//other types
	}
}




std::ifstream fstrm("buttons");
std::string entry("");
while(fstrm>>entry){
	std::stringstream ss(entry);
	std::string ID("");
	ss>>ID;
	mainmenu.addItem(ID.c_str(), ObjectCreator::object(ss));
}
