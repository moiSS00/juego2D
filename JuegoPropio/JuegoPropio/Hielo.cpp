#include "Hielo.h"

Hielo::Hielo(float x, float y, Game* game)
	: Enemy(x, y, game) {

	aMoving = new Animation("res/hieloEstado.png", width, height,
		800, 50, 3, 16, game);
	animation = aMoving;

}

