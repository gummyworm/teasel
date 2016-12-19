#include "battlestats.h"

/* NewBattleStats returns a new BattleStats component. */
struct BattleStats NewBattleStats(uint16_t def, uint16_t atk, uint16_t spd,
                                  uint16_t mag, uint16_t res) {
  struct BattleStats b = {.C = {.size = sizeof(struct BattleStats)},
                          .atk = atk,
                          .def = def,
                          .spd = spd,
                          .mag = mag,
                          .res = res};
  return b;
}
