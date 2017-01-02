#ifndef DESCRIPTION_H
#define DESCRIPTION_H

#include "entity.h"

struct Description {
	TV_COMPONENT
	const char *brief;
	const char *detailed;
};

struct Description NewDescription(const char *, const char *);

#endif
