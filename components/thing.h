#ifndef THING_H
#define THING_H

#include "entity.h"

/* Thing is component struct that contains data for physical objects. */
struct Thing {
	TV_COMPONENT
	uint16_t x, y; /* this thing's tile coordinates */
};

struct Thing NewThing();

#endif
