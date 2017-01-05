#ifndef COMPONENT_EXIT_H
#define COMPONENT_EXIT_H

#include "entity.h"

struct Exit {
	TV_COMPONENT
	void (*go)(); /* the scene function called when the exit is used */
};

struct Exit NewExit(void (*)());

#endif
