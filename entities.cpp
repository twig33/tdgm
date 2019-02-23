#include <iostream>

#include <managers.h>
#include <graphics.h>
#include <math.h>
#include <physics.h>

double globalSpeed = 1;
unsigned int last2 = 0;
long currEntityReserve = 128;
bool enemyLatch = 1;
EntityManager* Entities;
Player::Player(){
	hitbox.x = 100;
	hitbox.y = 100;
	hitbox.w = 50;
	hitbox.h = 50;
	sprite = Graphics->getTexture(playerTex);
	renderType = spriteRender;
	texture = new Texture;
	*texture = {sprite, &hitbox};
	reticleBox.w = 50;
	reticleBox.h = 50;
	reticleSprite = Graphics->getTexture(reticleTex);
	reticleTexture = new Texture;
	*reticleTexture = {reticleSprite, &reticleBox};
	type = player;
	collideType = 1 << type;
	collideMask = (1 << enemy);
}
Enemy::Enemy(){
	hitbox.x = Input->getInput()->mx;
	hitbox.y = Input->getInput()->my;
	hitbox.w = 50;
	hitbox.h = 50;
	sprite = Graphics->getTexture(enemyTex);
	renderType = spriteRender;
	texture = new Texture;
	*texture = {sprite, &hitbox};
	type = enemy;
	collideType = 1 << type;
	collideMask = (1 << projectile) | (1 << player);
}
Projectile::Projectile(){
	Player* plr = (Player*)(Entities->getEntities()[0]);
	hitbox.x = plr->hitbox.x;
	hitbox.y = plr->hitbox.y;
	this->x = hitbox.x;
	this->y = hitbox.y;
	hitbox.w = 50;
	hitbox.h = 50;
	sprite = Graphics->getTexture(projectileTex);
	renderType = spriteRender;
	texture = new Texture;
	*texture = {sprite, &hitbox};
	type = projectile;
	collideType = 1 << type;
	collideMask = (1 << enemy);
}
void Player::update(){
	//unsigned int last2;
	if (!this->hp){
		std::cout << "You fucked up\n";
	}
	reticleBox.x = Input->getInput()->mx - reticleBox.w/2;
	reticleBox.y = Input->getInput()->my - reticleBox.h/2;
	if (Input->getInput()->one && enemyLatch){
		enemyLatch = 0;
		Entities->getEntities().push_back(new Enemy);
	}
	if (!Input->getInput()->one){
		enemyLatch = 1;
	}
	if (Input->getInput()->m1 && ((SDL_GetTicks() - last2) > 200)){
		last2 = SDL_GetTicks();
		Projectile* pj = new Projectile;
		//Texture* reticle = (Texture*)(entities[1]);
		double x = reticleBox.x - hitbox.x;
		double y = reticleBox.y - hitbox.y;
		normalise(x, y);
		pj->speedX = x;
		pj->speedY = y;
		Entities->getEntities().push_back(pj);
	}
	if (Input->getInput()->w == Input->getInput()->s){
		speedY = 0;
	}else
	{
		speedY = (Input->getInput()->w ? -1 : 1)*moveSpeedY*globalSpeed;
	}
	if (Input->getInput()->d == Input->getInput()->a){
		speedX = 0;
	}else
	{
		speedX = (Input->getInput()->a ? -1 : 1)*moveSpeedY*globalSpeed;
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
void Player::renderMe(){             /////
	Graphics->render(texture, spriteRender);
	Graphics->render(reticleTexture, spriteRender);
}
void Enemy::renderMe(){           
	Graphics->render(texture, spriteRender);           
}
void Projectile::renderMe(){
	Graphics->render(texture, spriteRender);          ////
}
void Enemy::update(){
/*  if (Input->getInput()->one){			
		hitbox.x = Input->getInput()->mx;	 
		hitbox.y = Input->getInput()->my;	 
	}	
	*/
	if (!(this->hp)){
		delete this;
		dead = 1;
	}
}
void Projectile::update(){
		this->x += speedX*2*globalSpeed;
		this->y += speedY*2*globalSpeed;
		hitbox.x = (int)(this->x);
		hitbox.y = (int)(this->y);
		entity* challenger = Collision->colliding(&hitbox, collideType);
		if (challenger != NULL && challenger->type == enemy){
			((Enemy*)challenger)->hp -= 10;
			delete this; //https://www.youtube.com/watch?v=N5TWbeav7hI
			dead = 1;
			challenger = NULL;
		}
}
EntityManager::EntityManager(){
	entities.reserve(currEntityReserve);
	Entities = this;
}
std::vector<entity*>& EntityManager::getEntities(){
	return entities;
}
void EntityManager::setGlobalSpeed(double speed){
	globalSpeed = speed;
}
void EntityManager::removeEntity(long index){
	entities.erase(entities.begin()+index);
}
void EntityManager::renderEntities(){
	Graphics->entityRenderBegin();
	for (long i = 0; i < entities.size(); ++i){
		entities[i]->renderMe();
	}
	Graphics->entityRenderFinish();
}
void EntityManager::updateEntities(){
	long size = entities.size();
	if (size > currEntityReserve)
	{
		currEntityReserve *= 2;
		entities.reserve(currEntityReserve);
		Graphics->setColor(byellow);
		std::cout << "Warning: over " << currEntityReserve/2 << " entities\n";
		Graphics->setColor();
	}
	for (long i = 0; i < size; ++i){
		entities[i]->update();
		if (entities[i]->dead){
			removeEntity(i);
		}
	}
}
