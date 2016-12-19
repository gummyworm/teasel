#ifndef SYS_CONFIG_H
#define SYS_CONFIG_H

enum {
  MAX_BATTLERS = 32, /* maximum # of combatants in a battle */

  MAX_MOVERS = 32, /* maximum # of moving entities */

  TILE_CAPACITY = 16, /* number of entities that can be in 1 map tile */
  TILE_W = 32,        /* width of each tile in movement units */
  TILE_H = 32,        /* height of each tile in movement units */
  MAP_W = 128,        /* height of map in tiles */
  MAP_H = 128,        /* width of map in the tiles */
};

#endif
