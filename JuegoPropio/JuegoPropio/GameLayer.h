#pragma once

#include "Layer.h"

#include "Enemy.h"
#include "Background.h"
#include "Zombie.h"
#include "Projectile.h"
#include "Text.h"

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
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);

	int ticksEnemyDamage = 0;

	list<Enemy*> enemies;
	list<Actor*> plataformas;
	list<Zombie*> zombies; 
	list<Projectile*> projectiles;

	Background* background;
	Actor* backgroundSelector;
	Actor* backgroundContadorCerebros; 

	Actor* botonZombieBasico; 
	Actor* botonZombieRapido;
	Actor* botonZombieFuerte;

	bool clickedZombieBasico; 
	bool clickedZombieRapido; 
	bool clickedZombieFuerte;
	
	int cerebros;
	Text* textCerebros;
	Text* textCosteZombieBasico;
	Text* textCosteZombieRapido;
	Text* textCosteZombieFuerte;

	int costeZombieBasico = 10; 
	int costeZombieRapido = 20; 
	int costeZombieFuerte = 30; 
};

