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
	for (auto const& zombie : zombies) {
		zombie->draw();
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
			Zombie* zombie = new Zombie(plataforma->x, plataforma->y - 20, game);
			zombies.push_back(zombie);
			plataforma->clicked = false;
		}
	}
}


void GameLayer::mouseToControls(SDL_Event event) {
	// Modificaci�n de coordenadas por posible escalado
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
		// Por l�nea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			// Por car�cter (en cada l�nea)
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
		Plataforma* plataforma = new Plataforma(x, y + 10, game);
		plataformas.push_back(plataforma);
		break;
	}
	}
}
