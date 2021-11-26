#include "Hielo.h"

Hielo::Hielo(float x, float y, Game* game)
	: Enemy(x, y, game) {

	aMoving = new Animation("res/hieloEstado.png", width, height,
		800, 50, 3, 16, true, game);

	aAttacking = new Animation("res/hieloAtacar.png", width, height,
		400, 50, 3, 8, false, game);

	aDying = new Animation("res/hieloMorir.png", width, height,
		500, 50, 3, 10, false, game);

	animation = aMoving;

	lifes = 5;

	attackCadence = 100;

}

Projectile* Hielo::createProjectile() {
	return new Projectile(x, y, game, "res/disparoHielo.png");
}



