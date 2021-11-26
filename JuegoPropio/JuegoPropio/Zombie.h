#pragma once

#include "Actor.h"

class Zombie : public Actor
{
public:
	Zombie(float x, float y, Game* game);
	void update();
	void draw() override;
	void attack();
	void impacted();

	// Controlar ataque
	int attackCadence = 30;
	int attackTime = 0;
};


