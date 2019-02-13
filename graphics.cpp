#include <iostream>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <managers.h>

int SCREEN_HEIGHT = 480;
int SCREEN_WIDTH = 640;

const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;
GraphicsManager* Graphics;

void GraphicsManager::setColor(int color){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
GraphicsManager::GraphicsManager(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
	    setColor(red);
	    std::cout << SDL_GetError() << "\n";
	    setColor();
	}else{
		window = SDL_CreateWindow( "cheto tam", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		ourRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}
	initTextures();
	Graphics = this;
}
void GraphicsManager::render(void* pt, int type, color* Color){
	switch(type){
		case rectangleRender:
			{
				if (Color == NULL){
					static color* defaultColor = new color;
					defaultColor->r = 255;
					Color = defaultColor;
				}
				SDL_Rect* rect = (SDL_Rect*)pt;
				SDL_SetRenderDrawColor(ourRenderer, Color->r, Color->g, Color->b, Color->a);
				SDL_RenderFillRect(ourRenderer, rect);
			}
			break;
		case spriteRender:
		    SDL_RenderCopy(ourRenderer, ((Texture*)pt)->first, NULL, ((Texture*)pt)->second);
			break;
	}
}
/*void renderAll(const std::vector<entity*>& ents){
	SDL_SetRenderDrawColor(ourRenderer, 255, 255, 255, 0);
	SDL_RenderClear(ourRenderer);
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) { printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() ); }
	for(int i = 0; i < ents.size(); ++i){
		ents[i]->renderMe();
	}
	SDL_RenderPresent(renderer);
}*/
void GraphicsManager::entityRenderBegin(){
	SDL_SetRenderDrawColor(ourRenderer, 255, 255, 255, 0);
	SDL_RenderClear(ourRenderer);
}
void GraphicsManager::entityRenderFinish(){
	SDL_RenderPresent(ourRenderer);
}
SDL_Texture* GraphicsManager::loadFromPath(std::string path){
	SDL_Texture* a;
	SDL_Surface* load = IMG_Load(path.c_str());
	a = SDL_CreateTextureFromSurface(ourRenderer, load);
	return a;
}
void GraphicsManager::initTextures(){
	for(int i = 0; i < ALWAYS_LAST; ++i){
		textures.push_back (loadFromPath("resources/" + textureFnames[i]));
	}
}
SDL_Texture* GraphicsManager::getTexture(int type){
	return textures[type];
}