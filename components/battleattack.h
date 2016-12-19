#ifndef BATTLEATTACK_H
#define BATTLEATTACK_H

#include "entity.h"
#include <stdint.h>

enum {
  MOVE_DMGATTR,
};

struct BattleAttack {
  TV_COMPONENT
  uint16_t dmg;
  uint16_t effect;
  uint16_t pow;
};

struct BattleAttack NewBattleAttack(uint16_t);

#endif
