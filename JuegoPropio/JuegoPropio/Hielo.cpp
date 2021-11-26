#include "Hielo.h"

Hielo::Hielo(float x, float y, Game* game)
	: Enemy(x, y, game) {

	aMoving = new Animation("res/hieloEstado.png", width, height,
		800, 50, 3, 16, true, game);

	aDying = new Animation("res/hieloMorir.png", width, height,
		500, 50, 3, 10, false, game);

	animation = aMoving;

	lifes = 5;
}

void Hielo::loseLife() {
	if (lifes > 0) {
		lifes--;
	}
}

