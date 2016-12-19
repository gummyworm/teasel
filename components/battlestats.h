#ifndef BATTLESTATS_H
#define BATTLESTATS_H

#include "entity.h"
#include <stdint.h>

struct BattleStats {
  TV_COMPONENT
  uint16_t hp;
  uint16_t def;
  uint16_t atk;
  uint16_t spd;
  uint16_t mag;
  uint16_t res;
};

struct BattleStats NewBattleStats(uint16_t, uint16_t, uint16_t, uint16_t,
                                  uint16_t);

#endif
