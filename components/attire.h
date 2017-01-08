#ifndef ATTIRE_H
#define ATTIRE_H

#include "entity.h"

enum AttireLocation {
	ATTIRE_HEAD,
	ATTIRE_LEGS,
	ATTIRE_RIGHT_ARM,
	ATTIRE_LEFT_ARTM,
	ATTIRE_BODY,
	ATTIRE_LEFT_HAND,
	ATTIRE_RIGHT_HAND,
	ATTIRE_NUM_LOCATIONS,
};

struct Attire {
	TV_COMPONENT
	int protection[ATTIRE_NUM_LOCATIONS];
};

struct Attire NewAttire();

#endif
