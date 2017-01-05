#include "exit.h"

struct Exit NewExit(void (*go)()) {
	struct Exit e = {
	    .C = {.size = sizeof(struct Exit)}, .go = go,
	};
	return e;
}
