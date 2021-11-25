#pragma once

#include "Layer.h"

#include "Enemy.h"
#include "Background.h"

#include <list>
#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String

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

	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	int mapWidth;

};

