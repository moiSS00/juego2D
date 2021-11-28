#include "GameLayer.h"

#include "Gota.h"
#include "Hielo.h"
#include "Nube.h"

#include "ZombieBasico.h"
#include "ZombieRapido.h"
#include "ZombieFuerte.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	init();
}

void GameLayer::init() {

	cerebros = 100;
	textCerebros = new Text("", WIDTH * 0.09, HEIGHT * 0.19, 0, 0, 0, game);
	textCerebros->content = to_string(cerebros);

	textCosteZombieBasico = new Text("5", WIDTH * 0.235, HEIGHT * 0.19, 255, 255, 255, game);
	textCosteZombieRapido = new Text("10", WIDTH * 0.34, HEIGHT * 0.19, 255, 255, 255, game);
	textCosteZombieFuerte = new Text("15", WIDTH * 0.44, HEIGHT * 0.19, 255, 255, 255, game);

	clickedZombieBasico = false; 
	clickedZombieRapido = false; 
	clickedZombieFuerte = false; 

	// Inicializamos elementos de la interfaz
	background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	backgroundSelector = new Actor("res/selector.png", WIDTH * 0.33, HEIGHT * 0.10, 179, 66, game);
	backgroundContadorCerebros = new Actor("res/contadorCerebros.png", WIDTH * 0.07, HEIGHT * 0.10, 69, 65, game);
	botonZombieBasico = new Actor("res/iconoZombieBasico.png", WIDTH * 0.22, HEIGHT * 0.10, 35, 52, game);
	botonZombieRapido = new Actor("res/iconoZombieRapido.png", WIDTH * 0.32, HEIGHT * 0.10, 35, 52, game);
	botonZombieFuerte = new Actor("res/iconoZombieFuerte.png", WIDTH * 0.42, HEIGHT * 0.10, 35, 52, game);

	// Vaciar por si reiniciamos el juego
	enemies.clear(); 
	plataformas.clear(); 
	zombies.clear(); 
	projectiles.clear();

	// Cargar nivel
	loadMap("res/0.txt");
}

void GameLayer::update() {
	
	for (auto const& enemy : enemies) {
		enemy->update();
	}


	for (auto const& zombie : zombies) {
		zombie->update();
	}

	for (auto const& projectile : projectiles) {
		projectile->update();
	}

	for (auto const& enemy : enemies) {
		bool aux = false; 
		for (auto const& zombie : zombies) {
			if (zombie->y +10 == enemy->y && enemy->state == game->stateMoving) {
				aux = true;
				break;
			}
		}
		if (aux) {
			Projectile* projectile; 
			projectile = enemy->attack();
			if (projectile != NULL) {
				projectiles.push_back(projectile);
			}
		}
	}
	

	// Colisiones

	// Colision Zombie <-> Enemigo
	list<Enemy*> deleteEnemies;
	for (auto const& zombie : zombies) {
		for (auto const& enemy : enemies) {
			if (zombie->isOverlap(enemy) && zombie->containsPoint(enemy->x + 5, enemy->y)) {
				zombie->attack(); 
				if (ticksEnemyDamage == 30) {
					enemy->loseLife();
					ticksEnemyDamage = 0;
				}
				ticksEnemyDamage++;
			}
		}	
	}

	for (auto const& enemy : enemies) {
		if (enemy->state == game->stateDead) {
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();

			if (!eInList) {
				deleteEnemies.push_back(enemy);
				cerebros++;
				textCerebros->content = to_string(cerebros);
			}
		}
	}

	// Colisiones , Enemy - Projectile

	list<Zombie*> deleteZombies;
	list<Projectile*> deleteProjectiles;

	for (auto const& zombie : zombies) {
		for (auto const& projectile : projectiles) {
			if (zombie->isOverlap(projectile) && zombie->state != game->stateDead
				&& zombie->state != game->stateDying && projectile->y == zombie->y + 10
				&& projectile->x <= zombie->x) {
				zombie->loseLife(); 
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

			}
		}
	}

	for (auto const& zombie : zombies) {
		if (zombie->state == game->stateDead) {
			bool eInList = std::find(deleteZombies.begin(),
				deleteZombies.end(),
				zombie) != deleteZombies.end();

			if (!eInList) {
				deleteZombies.push_back(zombie);
			}
		}
	}


	// Fase de eliminación 

	// Eliminamos enemigos
	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
	}
	deleteEnemies.clear();

	for (auto const& delZombie : deleteZombies) {
		zombies.remove(delZombie);
	}
	deleteZombies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
	}
	deleteProjectiles.clear();


	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {

	background->draw();
	backgroundSelector->draw();
	backgroundContadorCerebros->draw(); 
	botonZombieBasico->draw();
	botonZombieRapido->draw();
	botonZombieFuerte->draw(); 
	textCerebros->draw();
	textCosteZombieBasico->draw();
	textCosteZombieRapido->draw(); 
	textCosteZombieFuerte->draw(); 

	for (auto const& enemy : enemies) {
		enemy->draw();
	}
	for (auto const& plataforma : plataformas) {
		plataforma->draw();
	}
	
	// Pintar por orden los zombies
	map<int, list<Zombie*>> zombiesFila;
	map<int, list<Zombie*>>::iterator it;

	for (auto const& zombie : zombies) {
		zombiesFila[zombie->y].push_back(zombie);
	}

	for (it = zombiesFila.begin(); it != zombiesFila.end(); it++)
	{
		for (auto const& zombie : it->second) {
			zombie->draw();
		}
	}

	zombiesFila.clear(); 

	for (auto const& projectile : projectiles) {
		projectile->draw();
	}


	SDL_RenderPresent(game->renderer); // Renderiza
}


void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		mouseToControls(event);
	}

	// procesar controles
	for (auto const& plataforma : plataformas) {
		if (plataforma->clicked) {
			if (clickedZombieBasico) {
				Zombie* zombie = new ZombieBasico(plataforma->x, plataforma->y - 20, game);
				zombies.push_back(zombie);
				cerebros--;
				textCerebros->content = to_string(cerebros);
			}
			if (clickedZombieRapido) {
				Zombie* zombie = new ZombieRapido(plataforma->x, plataforma->y - 20, game);
				zombies.push_back(zombie);
				cerebros--;
				textCerebros->content = to_string(cerebros);
			}
			if (clickedZombieFuerte) {
				Zombie* zombie = new ZombieFuerte(plataforma->x, plataforma->y - 20, game);
				zombies.push_back(zombie);
				cerebros--;
				textCerebros->content = to_string(cerebros);
			}
			plataforma->clicked = false;
		}
	}
}


void GameLayer::mouseToControls(SDL_Event event) {
	// Modificación de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;
	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {

		if (botonZombieBasico->containsPoint(motionX, motionY)) {
			clickedZombieBasico = true; 
			clickedZombieRapido = false; 
			clickedZombieFuerte = false; 
		}

		if (botonZombieRapido->containsPoint(motionX, motionY)) {
			clickedZombieRapido = true; 
			clickedZombieBasico = false; 
			clickedZombieFuerte = false;
		}

		if (botonZombieFuerte->containsPoint(motionX, motionY)) {
			clickedZombieFuerte = true;
			clickedZombieRapido = false;
			clickedZombieBasico = false;
		}

		for (auto const& plataforma : plataformas) {
			if (plataforma->containsPoint(motionX, motionY)) {
				plataforma->clicked = true; 
			}
		}

	}
	// Cada vez que se mueve
	if (event.type == SDL_MOUSEMOTION) {


	}
	// Cada vez que levantan el click
	if (event.type == SDL_MOUSEBUTTONUP) {

	}
}


void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			// Por carácter (en cada línea)
			for (int j = 0; j < line.length(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 50 / 2 + j * 50; // x central
				float y = 46 + i * 46; // y suelo
				loadMapObject(character, x, y);
			}
			cout << character << endl;
		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case 'G': {
		Enemy* enemie = new Gota(x, y, game);
		enemies.push_back(enemie);
		break;
	}
	case 'H': {
		Enemy* enemie = new Hielo(x, y, game);
		enemies.push_back(enemie);
		break;
	}
	case 'N': {
		Enemy* enemie = new Nube(x, y, game);
		enemies.push_back(enemie);
		break;
	}
	case 'Z': {
		Actor* plataforma = new Actor("res/plataforma.png", x, y + 10, 32, 40, game); 
		plataformas.push_back(plataforma);
		break;
	}
	}
}

