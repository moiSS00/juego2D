#pragma once

#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy(float x, float y, Game* game);
	void update();
	void loseLife();
	void draw() override;
	void attack(); 

	int lifes;

	// Controlar ataque
	int attackCadence; 
	int attackTime = 0;
};


