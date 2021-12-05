#include "Gota.h"

Gota::Gota(float x, float y, Game* game)
	: Enemy(x, y, game) {

	aMoving = new Animation("res/gotaEstado.png", width, height,
		800, 50, 3, 16, true, game, game->stateMoving);

	aAttacking = new Animation("res/gotaAtacar.png", width, height,
		500, 50, 3, 10, false, game, game->stateAttacking);

	aDying = new Animation("res/gotaMorir.png", width, height,
		500, 50, 3, 10, false, game, game->stateDying);

	animation = aMoving;

	lifes = 6;

	cerebrosDados = 10; 

	attackCadence = 60; 

}

Projectile* Gota::createProjectile() {
	return new Projectile(x, y, 5, game, "res/disparoGota.png");
}



