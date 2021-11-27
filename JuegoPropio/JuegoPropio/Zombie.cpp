#include "Zombie.h"

Zombie::Zombie(float x, float y, Game* game)
	: Actor("", x, y, 60, 70, game) {
	state = game->stateMoving;
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

void Zombie::loseLife() {
	if (lifes > 0) {
		lifes--;
	}
	else {
		state = game->stateDying;
	}
}



