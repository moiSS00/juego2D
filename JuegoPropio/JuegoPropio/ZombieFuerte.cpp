#include "ZombieFuerte.h"

ZombieFuerte::ZombieFuerte(float x, float y, Game* game)
	: Zombie(x, y, game) {

	aMoving = new Animation("res/zombieFuerteCaminar.png", width, height,
		600, 72, 3, 10, true, game, game->stateMoving);

	aAttacking = new Animation("res/zombieFuerteAtacar.png",
		width, height, 480, 72, 3, 8, false, game, game->stateAttacking);

	aDying = new Animation("res/zombieFuerteMorir.png",
		width, height, 720, 50, 3, 12, false, game, game->stateDying);

	animation = aMoving;

	lifes = 50;

	damage = 6;
	
	baseVX = -1;
}
