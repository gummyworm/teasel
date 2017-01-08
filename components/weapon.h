#ifndef WEAPON_H
#define WEAPON_H

#include "entity.h"

struct Weapon {
	TV_COMPONENT
	int damage;
};

struct Weapon NewWeapon(int);

#endif
