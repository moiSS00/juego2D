#pragma once

#include "Actor.h"
#include "Projectile.h" 

class Enemy : public Actor
{
public:
	Enemy(float x, float y, Game* game);
	void update();
	void loseLife();
	void draw() override;
	Projectile* attack();
	virtual Projectile* createProjectile() { return NULL; };

	int lifes;

	// Controlar ataque
	int attackCadence; 
	int attackTime = 0;
};


