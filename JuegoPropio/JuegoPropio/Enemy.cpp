#include "Enemy.h"

Enemy::Enemy(float x, float y, Game* game)
	: Actor("", x, y, 50, 50, game) {
}

void Enemy::draw() {
	animation->draw(x, y);
}

