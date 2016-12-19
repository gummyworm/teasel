#ifndef MOTIONSTATS_H
#define MOTIONSTATS_H

#include "entity.h"
#include <stdint.h>

/* MotionStats is a component containing speeds for various motions. */
struct MotionStats {
  TV_COMPONENT
  uint16_t turn;
  uint16_t strafe;
  uint16_t backpedal;
  uint16_t forward;
  uint16_t run;
  uint16_t velX;
  uint16_t velY;
  uint16_t velZ;
};

struct MotionStats NewMotionStats(uint16_t, uint16_t, uint16_t, uint16_t,
                                  uint16_t);

#endif
