#ifndef MANAGERS_H
#define MANAGERS_H

#include <graphics.h>
#include <gamestate.h>
#include <entities.h>
#include <physics.h>
#include <input.h>
#include <ui.h>

extern EntityManager* Entities;
extern InputManager* Input;
extern GraphicsManager* Graphics;
extern CollisionManager* Collision;
extern GameStateManager* Gamestate;
extern UIManager* UI;

#endif