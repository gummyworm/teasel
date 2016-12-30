#include "motionstats.h"

/* NewMotionStats returns a new MotionStats component. */
struct MotionStats NewMotionStats(uint16_t t, uint16_t s, uint16_t b,
                                  uint16_t f, uint16_t r) {
	struct MotionStats m = {
	    .C = {.size = sizeof(struct MotionStats)},
	    .turn = t,
	    .strafe = s,
	    .backpedal = b,
	    .forward = f,
	    .run = r,
	    .velX = 0,
	    .velY = 0,
	    .velZ = 0,
	};
	return m;
}
