#include <entities.h>
#include <graphics.h>
#include <input.h>
#include <math.h>
#include <iostream>
typedef void (*func)(void);
double globalSpeed = 1;
unsigned int last2 = 0;
std::vector<entity> entities;
long currEntityReserve = 128;
std::vector<entity>& getEntities(){
	static bool once = [](){
		entities.reserve(128);
		return true;
	} ();
	return entities;
}
Player::Player(){
	hitbox.x = 100;
	hitbox.y = 100;
	hitbox.w = 50;
	hitbox.h = 50;
}
Enemy::Enemy(){
	hitbox.x = 100;
	hitbox.y = 100;
	hitbox.w = 50;
	hitbox.h = 50;
}
Projectile::Projectile(){
	Player* plr = (Player*)(getEntities()[0].first);
	hitbox.x = plr->hitbox.x;
	hitbox.y = plr->hitbox.y;
	this->x = hitbox.x;
	this->y = hitbox.y;
	hitbox.w = 50;
	hitbox.h = 50;
}
void Player::update(){
	//unsigned int last2;
	if (!this->hp){
		std::cout << "You fucked up\n";
	}

	if (getInput()->m1 && ((SDL_GetTicks() - last2) > 200)){
		last2 = SDL_GetTicks();
		Projectile* pj = new Projectile;
		Texture* reticle = (Texture*)(entities[1].first);
		double x = reticle->second->x - reticle->second->w/2 - hitbox.x;
		double y = reticle->second->y - reticle->second->h/2 - hitbox.y;
		normalise(x, y);
		pj->speedX = x;
		pj->speedY = y;
		entities.push_back({pj, projectile});
	}
	if (getInput()->w == getInput()->s){
		speedY = 0;
	}else
	{
		speedY = (getInput()->w ? -1 : 1)*moveSpeedY*globalSpeed;
	}
	if (getInput()->d == getInput()->a){
		speedX = 0;
	}else
	{
		speedX = (getInput()->a ? -1 : 1)*moveSpeedY*globalSpeed;
	}
	bool x = speedX != 0;
	bool y = speedY != 0;
	double deltaX = speedX < 0 ? speedX * -1 : speedX;
	double deltaY = speedY < 0 ? speedY * -1 : speedY;
	normalise(deltaX, deltaY);
	if (x){
		this->x += (speedX * deltaX);
		hitbox.x = (int)(this->x);
		speedX = 0;
	}
	if (y){
		this->y += (speedY * deltaY);
		hitbox.y = (int)(this->y);
		speedY = 0;
	}
}

void Enemy::update(){
	if (getInput()->one){
		hitbox.x = getInput()->mx;
		hitbox.y = getInput()->my;
	}
}
void Projectile::update(){
		this->x += speedX*2*globalSpeed;
		this->y += speedY*2*globalSpeed;
		hitbox.x = (int)(this->x);
		hitbox.y = (int)(this->y);
}
void updateAll(std::vector<entity>& entities){
	int size = entities.size();
	if (size > currEntityReserve)
	{
		currEntityReserve *= 2;
		entities.reserve(currEntityReserve);
		setColor(byellow);
		std::cout << "Warning: over " << currEntityReserve/2 << " entities\n";
		setColor();
	}
	for (int i = 0; i < size; ++i){
		switch(entities[i].second){
			case player:
				((Player*)(entities[i].first))->update();
				break;
			case enemy:
				((Enemy*)(entities[i].first))->update();
				break;
			case projectile:
				((Projectile*)(entities[i].first))->update();
				break;
		}
	}
	if (getInput()->one){
		entities.push_back({new Enemy, enemy});   //если зажать двигаецо
    }
}
void setGlobalSpeed(double speed){
	globalSpeed = speed;
}
