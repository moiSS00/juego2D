#include "Zombie.h"

Zombie::Zombie(float x, float y, Game* game)
	: Actor("", x, y, 60, 70, game) {

	aMoving = new Animation("res/zombieBasicoCaminar.png", width, height,
		600, 72, 3, 10, game);
	animation = aMoving;

}

void Zombie::update() {
	// Actualizar la animación
	animation->update();
}

void Zombie::draw() {
	animation->draw(x, y);
}

