#include "ZombieRapido.h"

ZombieRapido::ZombieRapido(float x, float y, Game* game)
	: Zombie(x, y, game) {

	aMoving = new Animation("res/zombieRapidoCaminar.png", width, height,
		600, 66, 3, 10, true, game);

	aAttacking = new Animation("res/zombieRapidoAtacar.png",
		width, height, 480, 66, 3, 8, false, game);

	aDying = new Animation("res/zombieRapidoMorir.png",
		width, height, 720, 55, 3, 12, false, game);

	animation = aMoving;

	lifes = 3;

	vx = -3;
}