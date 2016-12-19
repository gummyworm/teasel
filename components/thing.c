#include "thing.h"

/* NewThing creates a new Thing component and returns it. */
struct Thing NewThing() {
  struct Thing t = {.C = {.size = sizeof(struct Thing)}};
  return t;
}
