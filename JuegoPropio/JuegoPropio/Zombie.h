#pragma once

#include "Actor.h"

class Zombie : public Actor
{
public:
	Zombie(float x, float y, Game* game);
	void update();
	void draw() override;
};


