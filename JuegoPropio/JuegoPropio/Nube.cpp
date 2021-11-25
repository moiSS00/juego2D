#include "Nube.h"

Nube::Nube(float x, float y, Game* game)
	: Enemy(x, y, game) {

	aMoving = new Animation("res/nubeEstado.png", width, height,
		400, 50, 3, 8, game);
	animation = aMoving;

}

