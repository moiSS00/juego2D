#pragma once

#include "Game.h"
#include "Animation.h" 

class Actor
{
public:
	Actor(string filename, float x, float y, int width, int height, Game* game);
	virtual void draw();
	SDL_Texture* texture;
	int x;
	int y;
	float vx;
	float vy;
	int width;
	int height;
	int fileWidth;
	int fileHeight;
	Game* game; // referencia al juego

	Animation* aMoving;
	Animation* animation; // Referencia a la animación mostrada

};

