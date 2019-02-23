#ifndef ENTITIES_INCLUDED
#define ENTITIES_INCLUDED

#include <SDL.h>
#include <input.h>
#include <vector>
#include <iostream>

enum {player, enemy, projectile, tex};
const int playerIndex = 0;
//const int reticleIndex = 1;
typedef std::pair<SDL_Texture*, SDL_Rect*> Texture;
//typedef std::pair<void*, int> entity;
class entity {
	public:
		virtual void update() {};
		virtual void renderMe() {};
		unsigned int collideType;
		unsigned int collideMask;
		unsigned int type;
		SDL_Rect hitbox;
		bool dead = 0;
};
class EntityManager{
	public:
		double globalSpeed = 1;
		long currEntityReserve = 128;
		std::vector<entity*>& getEntities();
		void removeEntity(long index);
		void updateEntities();
		void renderEntities();
		void setGlobalSpeed(double speed);
		EntityManager();
		
	private:
		std::vector<entity*> entities;
};

//extern EntityManager* entitymMg;

class Player : public entity{
	public:
		virtual void update(); 
		virtual void renderMe();
		
		double x = 100;
		double y = 100;
		unsigned int hp = 100;
		unsigned int def = 10;
		double moveSpeedX = 2;
		double moveSpeedY = 2;
		double speedX = 0;
		double speedY = 0;
		SDL_Texture* sprite;
		Texture* texture;
		SDL_Rect reticleBox;
		SDL_Texture* reticleSprite;
		Texture* reticleTexture;
		unsigned int renderType;
		Player();
};

class Enemy : public entity{
	public:
		virtual void update();
		virtual void renderMe();
		
		unsigned int hp = 100;
		unsigned int def = 0;
		double moveSpeedX = 2;
		double moveSpeedY = 2;
		double speedX = 0;
		double speedY = 0;
		SDL_Texture* sprite;
		Texture* texture;
		unsigned int renderType;
		Enemy();
};

class Projectile : public entity{
	public:
		virtual void update(); 
		virtual void renderMe();
		
		double x;
		double y;
		double speedX = 0;
		double speedY = 0;
		SDL_Texture* sprite;
		Texture* texture;
		unsigned int renderType;
		long index;
		Projectile();
};


#endif