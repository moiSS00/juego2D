#include "Enemy.h"

Enemy::Enemy(float x, float y, Game* game)
	: Actor("", x, y, 50, 50, game) {
	state = game->stateMoving; 
}

void Enemy::update() {

	if (attackTime > 0) {
		attackTime--;
	}

	// Actualizar la animación
	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
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
	}
	if (state == game->stateAttacking) {
		animation = aAttacking;
	}
	if (state == game->stateDying) {
		animation = aDying;
	}

}

void Enemy::draw() {
	animation->draw(x, y);
}

Projectile* Enemy::attack() {
	if (attackTime == 0 && state == game->stateMoving) {
		state = game->stateAttacking;
		attackTime = attackCadence;
		aAttacking->currentFrame = 0;
		return createProjectile(); 
	}
	else {
		return NULL; 
	}
}


void Enemy::loseLife(int damage) {
	if (lifes - damage > 0) {
		lifes -= damage; 
	}
	else {
		state = game->stateDying; 
	}
}