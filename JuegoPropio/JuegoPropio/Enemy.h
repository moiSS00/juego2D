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
	void impacted();

	int lifes;
};


