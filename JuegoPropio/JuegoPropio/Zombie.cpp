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

	/**
	* Puede darse el caso de que el zombie cambie su estado a dyung antes de acabar una animacion de ataque, por lo que tenemos 
	* que tener un control más exhaustivo sobre la animación que ha finlizado. 
	**/

	// Acabo la animación
	if (endAnimation) {
		if (animation->id == game->stateAttacking) { // Si la animacion era de ataque
			if (state == game->stateAttacking) { // Comprobamos si no se corta animacion con la de morir
				state = game->stateMoving; // Sigue moviendose
			}
		}
		if (animation->id == game->stateDying) { // Si la animacion era de muerte 
			state = game->stateDead; // Pasa a estado final
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

	if (state == game->stateMoving) {
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



