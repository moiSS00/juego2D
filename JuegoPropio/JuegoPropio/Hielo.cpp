#include "Hielo.h"

Hielo::Hielo(float x, float y, Game* game)
	: Enemy(x, y, game) {

	aMoving = new Animation("res/hieloEstado.png", width, height,
		800, 50, 3, 16, true, game, game->stateMoving);

	aAttacking = new Animation("res/hieloAtacar.png", width, height,
		400, 50, 3, 8, false, game, game->stateAttacking);

	aDying = new Animation("res/hieloMorir.png", width, height,
		500, 50, 3, 10, false, game, game->stateDying);

	animation = aMoving;

	lifes = 20;

	cerebrosDados = 30;

	attackCadence = 150;

}

Projectile* Hielo::createProjectile() {
	return new Projectile(x, y, 3, game, "res/disparoHielo.png");
}



