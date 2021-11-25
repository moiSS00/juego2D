#pragma once

#include "Layer.h"

#include "Enemy.h"
#include "Background.h"

#include <list>

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;

	Background* background;
	list<Enemy*> enemies;
};

