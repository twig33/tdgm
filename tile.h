#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include <SDL_image.h>

class Tile
{

	public:

//	TileType tileType;

	Tile();
			
	Tile(int x, int y, int tileType); //я немного запутался насчет того что я хочу сделать с тилетипом ну лан

	void render(SDL_Rect& camera);
	
	int getType

	private:
	//тип тайла
	int mType;
}

#endif