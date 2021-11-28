#pragma once

#include "Actor.h"

class Zombie : public Actor
{
public:
	Zombie(float x, float y, Game* game);
	void update();
	void draw() override;
	void attack();
	void loseLife(int damage);

	int lifes;
	int damage; 

	// Controlar ataque
	int attackCadence = 30;
	int attackTime = 0;
};


