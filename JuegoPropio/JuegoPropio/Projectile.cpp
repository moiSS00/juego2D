#include "Projectile.h"

Projectile::Projectile(float x, float y, Game* game, string animationFileName) :
	Actor("", x, y, 50, 50, game) {

	aDisparo = new Animation(animationFileName, width, height,
		200, 50, 3, 4, true, game);

	vx = 9;
}

void Projectile::update() {
	x = x + vx;
	aDisparo->update();
}

void Projectile::draw() {
	aDisparo->draw(x, y);
}


