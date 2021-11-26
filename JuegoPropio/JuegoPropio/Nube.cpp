#include "Nube.h"

Nube::Nube(float x, float y, Game* game)
	: Enemy(x, y, game) {

	aMoving = new Animation("res/nubeEstado.png", width, height,
		400, 50, 3, 8, true, game);
	animation = aMoving;

	lifes = 1;
}

void Nube::loseLife() {
	if (lifes > 0) {
		lifes--;
	}
}

