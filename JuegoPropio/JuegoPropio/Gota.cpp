#include "Gota.h"

Gota::Gota(float x, float y, Game* game)
	: Enemy(x, y, game) {

	aMoving = new Animation("res/gotaEstado.png", width, height,
		800, 50, 3, 16, true, game);

	aAttacking = new Animation("res/gotaAtacar.png", width, height,
		500, 50, 3, 10, false, game);

	aDying = new Animation("res/gotaMorir.png", width, height,
		500, 50, 3, 10, false, game);

	animation = aMoving;

	lifes = 1;

	cerebrosDados = 10; 

	attackCadence = 50; 

}

Projectile* Gota::createProjectile() {
	return new Projectile(x, y, game, "res/disparoGota.png");
}



