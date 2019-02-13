#include <iostream>			//commit test
#include <vector>
#include <windows.h>
#include <string>
#include "SDL.h"
#include <physics.h>
#include <managers.h>
#include <stack>
#include <gamestate.h>


EntityManager entityMg;
InputManager inputMg;
GraphicsManager graphicsMg;


bool updateEvts(){
	static SDL_Event e;
	while(SDL_PollEvent(&e) != 0){
		if (e.type == SDL_QUIT){
			return 1;
		}else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP || e.type == SDL_MOUSEMOTION 
			      || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
			Input->updateInput(e);
		}
	}	
	return 0;
}

int main(int argc, char* argv[]){
	Graphics->setColor(green);
	std::cout << "\n\n\n" + hello + "\n\n\n";
	Graphics->setColor((white << 4) + cyan);
	bool quit = 0;
	Entities->getEntities().push_back(new Player);
		while (!quit){
			unsigned int before = SDL_GetTicks();
		
			quit = updateEvts(); //and input
			Entities->updateEntities();
			Entities->renderEntities();
		
			unsigned int diff = SDL_GetTicks() - before;
			if (diff < 1000/120) {SDL_Delay(1000/120 - diff); Entities->setGlobalSpeed(1);}
			else {Entities->setGlobalSpeed((double)diff / (((double)1000)/120));}
		}
	SDL_Quit();
	return 0;
}