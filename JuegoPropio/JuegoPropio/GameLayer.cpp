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
	loadMap("res/0.txt");
}

void GameLayer::processControls() {
}

void GameLayer::update() {
	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	background->draw();
	for (auto const& enemy : enemies) {
		enemy->draw();
	}
	SDL_RenderPresent(game->renderer); // Renderiza
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
			mapWidth = line.length() * 40; // Ancho del mapa en pixels
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 40 / 2 + j * 40; // x central
				float y = 32 + i * 32; // y suelo
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
		// modificación para empezar a contar desde el suelo.
		enemie->y = enemie->y - enemie->height / 2;
		enemies.push_back(enemie);
		break;
	}
	case 'H': {
		Enemy* enemie = new Hielo(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemie->y = enemie->y - enemie->height / 2;
		enemies.push_back(enemie);
		break;
	}
	case 'N': {
		Enemy* enemie = new Nube(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemie->y = enemie->y - enemie->height / 2;
		enemies.push_back(enemie);
		break;
	}
	}
}

