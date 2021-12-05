#include "ZombieBasico.h"

ZombieBasico::ZombieBasico(float x, float y, Game* game)
	: Zombie(x, y, game) {

	aMoving = new Animation("res/zombieBasicoCaminar.png", width, height,
		600, 72, 3, 10, true, game, game->stateMoving);

	aAttacking = new Animation("res/zombieBasicoAtacar.png",
		width, height, 480, 72, 3, 8, false, game, game->stateAttacking);

	aDying = new Animation("res/zombieBasicoMorir.png",
		width, height, 720, 50, 3, 12, false, game, game->stateDying);

	animation = aMoving;

	lifes = 45;

	damage = 5;

	baseVX = -1.25;
}

