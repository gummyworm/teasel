#include "attire.h"

/* NewAttire creates and returns a new Attire component. */
struct Attire NewAttire() {
	struct Attire a = {
	    .C = {.size = sizeof(struct Attire)}, .protection = {},
	};
	return a;
}
