#include "GameLayer.h"

#include "Gota.h"
#include "Hielo.h"
#include "Nube.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	init();
}

void GameLayer::init() {
	background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	enemies.clear(); // Vaciar por si reiniciamos el juego
	plataformas.clear(); 
	zombies.clear(); 
	loadMap("res/0.txt");
}

void GameLayer::update() {
	for (auto const& enemy : enemies) {
		enemy->update();
	}


	for (auto const& zombie : zombies) {
		zombie->update();
	}

	for (auto const& enemy : enemies) {
		bool aux = false; 
		for (auto const& zombie : zombies) {
			if (zombie->y +10 == enemy->y) {
				aux = true;
				break;
			}
		}
		if (aux) {
			cout << "ENTROOOOOOOOOOOOOOOOO" << endl;
			enemy->attack(); 
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
			}
		}
	}

	// Fase de eliminación 

	// Eliminamos enemigos
	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
	}

	deleteEnemies.clear();

	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	background->draw();
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
			Zombie* zombie = new Zombie(plataforma->x, plataforma->y - 20, game);
			zombies.push_back(zombie);
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

