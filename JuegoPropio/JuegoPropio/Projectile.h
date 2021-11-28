#pragma once

#include "Actor.h"

class Projectile : public Actor
{
public:
	Projectile(float x, float y, int damage,Game* game, string animationFileName);
	void update();
	void draw() override;

	Animation* aDisparo;
	int damage; 
};


