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
	enemies.push_back(new Gota(300, 50, game));
	enemies.push_back(new Hielo(300, 200, game));
	enemies.push_back(new Nube(320, 220, game));
}

void GameLayer::processControls() {
}

void GameLayer::update() {
	for (auto const& enemy : enemies) {
		enemy->update();
	}
	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	background->draw();
	for (auto const& enemy : enemies) {
		enemy->draw();
	}
	SDL_RenderPresent(game->renderer); // Renderiza
}

