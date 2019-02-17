#ifndef PHYSICS_INCLUDED
#define PHYSICS_INCLUDED

#include <SDL.h>
#include <managers.h>

bool rectColliding(SDL_Rect* one, SDL_Rect* two);
entity* colliding(SDL_Rect* rect, unsigned int coltype);
class Collision{
	public:
		entity* challenger;
		SDL_Rect* collisionRect;
		float xDirection;
		float yDirection;
};
class CollisionManager{
	public:
		entity* colliding(SDL_Rect* rect, unsigned int coltype);
		bool pointIn(SDL_Rect rect, int x, int y);
	private:
		rectColliding(SDL_Rect* one, SDL_Rect* two);
};
#endif