#ifndef GRAPHICS_INCLUDED
#define GRAPHICS_INCLUDED

#include <vector>
#include <SDL.h>
#include <string>

enum {rectangleRender, spriteRender};
enum {playerTex, enemyTex, projectileTex, reticleTex, buttonDefaultTex, buttonClickTex, buttonHoverTex, ALWAYS_LAST};
typedef std::pair<SDL_Texture*, SDL_Rect*> Texture;


struct color{
	int r = 0;
	int g = 0;
	int b = 0;
	int a = 255;
};


enum colors {black, blue, green, cyan, red, purple, yellow, white, gray, bblue, bgreen, bcyan, bred, bpurple, byellow, bwhite};

class GraphicsManager{
	public:
		void setColor(int color = white);
		GraphicsManager();
		void render(void* pt, int type, color* Color = NULL);
		void entityRenderBegin();
		void entityRenderFinish();
		SDL_Texture* getTexture(int type);	
	private:
		void initTextures();	
		SDL_Renderer* ourRenderer;
		SDL_Window* window;
		std::vector<SDL_Texture*> textures;
		std::vector<std::string> textureFnames = {"player.png", "enemy.png", "projectile.png", "reticle.png", "buttonDefaultTex.png", "buttonClickTex.png", "buttonHoverTex.png"};
		SDL_Texture* loadFromPath(std::string path);
};
#endif