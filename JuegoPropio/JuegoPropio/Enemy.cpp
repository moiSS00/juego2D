#include "Enemy.h"

Enemy::Enemy(float x, float y, Game* game)
	: Actor("", x, y, 50, 50, game) {
}

void Enemy::update() {
	// Actualizar la animación
	animation->update();
}

void Enemy::draw() {
	animation->draw(x, y);
}

