#pragma once

#include "Layer.h"

#include "Enemy.h"
#include "Background.h"
#include "Zombie.h"

#include <list>
#include <map> 
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
	void mouseToControls(SDL_Event event); // USO DE MOUSE

	Background* background;
	list<Enemy*> enemies;
	list<Actor*> plataformas;
	map<int, list<Zombie*>> zombies; // Almacena zombies por fila

	void loadMap(string name);
	void loadMapObject(char character, float x, float y);

};

