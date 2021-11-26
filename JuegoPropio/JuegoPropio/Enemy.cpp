#include "Enemy.h"

Enemy::Enemy(float x, float y, Game* game)
	: Actor("", x, y, 50, 50, game) {
	state = game->stateMoving; 
}

void Enemy::update() {
	// Actualizar la animación
	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
		}
	}

	if (state == game->stateMoving) {
		animation = aMoving;
	}
	if (state == game->stateDying) {
		animation = aDying;
	}

}

void Enemy::draw() {
	animation->draw(x, y);
}

void Enemy::attack() {
	state = game->stateAttacking; 
}

void Enemy::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}