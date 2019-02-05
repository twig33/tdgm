#ifndef GRAPHICS_INCLUDED
#define GRAPHICS_INCLUDED

#include <vector>
#include <SDL.h>
#include <string>

enum {rectangleRender, spriteRender};
enum {playerTex, enemyTex, projectileTex, reticleTex, ALWAYS_LAST};
typedef std::pair<SDL_Texture*, SDL_Rect*> Texture;
struct color{
	int r = 0;
	int g = 0;
	int b = 0;
	int a = 255;
};
enum colors {black, blue, green, cyan, red, purple, yellow, white, gray, bblue, bgreen, bcyan, bred, bpurple, byellow, bwhite};
void setColor(int color = white);
void entityRenderBegin();
void entityRenderFinish();
void render(void* pt, int type, color* Color = NULL);
class GraphicsManager{
	public:
		void setColor(int color = white);
		void render(void* pt, int type, color* Color = NULL);
	private:
		SDL_Renderer* ourRenderer;
		std::vector<SDL_Texture*> textures;
		std::vector<std::string> textureFnames = {"player.png", "enemy.png", "projectile.png", "reticle.png"};
};
#endif