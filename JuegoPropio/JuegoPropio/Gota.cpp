#include "Gota.h"

Gota::Gota(float x, float y, Game* game)
	: Enemy(x, y, game) {

	aMoving = new Animation("res/gotaEstado.png", width, height,
		800, 50, 3, 16, game);
	animation = aMoving;

	lifes = 0;

}

void Gota::loseLife() {
	if (lifes > 0) {
		lifes--;
	}
}

