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
		vx = baseVX; 
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

bool Zombie::attack() {
	if (attackTime == 0 && state == game->stateMoving) {
		state = game->stateAttacking;
		attackTime = attackCadence;
		aAttacking->currentFrame = 0;
		return true; 
	}
	return false; 
}

void Zombie::loseLife(int damage) {
	if (lifes - damage > 0) {
		lifes -= damage;
	}
	else {
		state = game->stateDying;
	}
}



