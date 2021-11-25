#include "Enemy.h"

Enemy::Enemy(float x, float y, Game* game)
	: Actor("", x, y, 50, 50, game) {
	vx = 1;
}

void Enemy::update() {

	// Actualizar la animación
	animation->update();

	x = x + vx;
	if (x <= 0 || x >= WIDTH) {
		vx = vx * -1;
	}
}

void Enemy::draw() {
	animation->draw(x, y);
}

