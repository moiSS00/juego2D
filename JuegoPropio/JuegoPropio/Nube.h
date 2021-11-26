#include "Enemy.h"

class Nube : public Enemy
{
public:
	Nube(float x, float y, Game* game);
	Projectile* createProjectile() override;
};

