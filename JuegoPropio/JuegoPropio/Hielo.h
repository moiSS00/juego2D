#include "Enemy.h"

class Hielo : public Enemy
{
public:
	Hielo(float x, float y, Game* game);
	Projectile* createProjectile() override;
};

