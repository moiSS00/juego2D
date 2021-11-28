#include "Nube.h"

Nube::Nube(float x, float y, Game* game)
	: Enemy(x, y, game) {

	aMoving = new Animation("res/nubeEstado.png", width, height,
		400, 50, 3, 8, true, game);

	aAttacking = new Animation("res/nubeAtacar.png", width, height,
		400, 50, 3, 8, false, game);

	aDying = new Animation("res/nubeMorir.png", width, height,
		400, 50, 3, 8, false, game);

	animation = aMoving;

	lifes = 1;

	cerebrosDados = 50;

	attackCadence = 75;

}

Projectile* Nube::createProjectile() {
	return new Projectile(x, y, 2, game, "res/disparoNube.png");
}


