#include "description.h"

struct Description NewDescription(const char *brief, const char *detailed) {
	struct Description d = {.C = {.size = sizeof(struct Description)},
	                        .brief = brief,
	                        .detailed = detailed};
	return d;
}
