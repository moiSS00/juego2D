#include "Gota.h"

Gota::Gota(float x, float y, Game* game)
	: Enemy(x, y, game) {

	aMoving = new Animation("res/gotaEstado.png", width, height,
		800, 50, 3, 16, true, game);

	aDying = new Animation("res/gotaMorir.png", width, height,
		500, 50, 3, 10, false, game);

	animation = aMoving;

	lifes = 1;

}


