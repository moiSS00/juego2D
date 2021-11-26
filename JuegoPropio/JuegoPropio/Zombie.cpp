#include "Zombie.h"

Zombie::Zombie(float x, float y, Game* game)
	: Actor("", x, y, 60, 70, game) {

	state = game->stateMoving;

	aMoving = new Animation("res/zombieBasicoCaminar.png", width, height,
		600, 72, 3, 10, true, game);

	aAttacking = new Animation("res/zombieBasicoAtacar.png",
		width, height, 480, 72, 3, 8, false, game);

	aDying = new Animation("res/zombieBasicoMorir.png",
		width, height, 720, 50, 3, 12, false, game);

	animation = aMoving;

	vx = -1;
}

void Zombie::update() {

	if (attackTime > 0) {
		attackTime--;
	}

	// Actualizar la animación
	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba atacando
		if (state == game->stateAttacking) {
			state = game->stateMoving;
		}
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
		}
	}

	if (state == game->stateMoving) {
		animation = aMoving;
		vx = -1;
	}
	if (state == game->stateDying) {
		animation = aDying;
		vx = 0;
	}
	if (state == game->stateAttacking) {
		animation = aAttacking;
		vx = 0;
	}

	if (state != game->stateDying) {
		x = x + vx;
	}

}

void Zombie::draw() {
	animation->draw(x, y);
}

void Zombie::attack() {
	if (attackTime == 0) {
		state = game->stateAttacking;
		attackTime = attackCadence;
		aAttacking->currentFrame = 0;
	}
	
}

void Zombie::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}



