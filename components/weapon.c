#include "weapon.h"

/* NewWeapon creates a weapon that deals damage points of damage. */
struct Weapon NewWeapon(int damage) {
	struct Weapon w = {.C = {.size = sizeof(struct Weapon)},
	                   .damage = damage};
	return w;
}
