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


void Enemy::loseLife() {
	if (lifes > 0) {
		lifes--;
	}
	else {
		state = game->stateDying; 
	}
}