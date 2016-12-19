#include <stdbool.h>
#include <string.h>
#include "draw.h"
#include "entity.h"
#include "system.h"
#include "sys_config.h"

#include "components/cam.h"
#include "components/enum.h"
#include "systems/sys_map.h"

/* MapTile is the basic unit that the comprises the map. */
struct MapTile{
	struct tv_Entity *contents[TILE_CAPACITY];
};

/* worldMap represents the game scene. */
static struct MapTile worldMap[MAP_H][MAP_W];

/* gets the tile that contains the given world coordinate. */
static struct MapTile * getTile(unsigned x, unsigned y)
{
	return worldMap[x / TILE_W] + (y / TILE_H);
}

/* MapTile draws all entities within t. */
static void drawTile(struct MapTile *t)
{
	int i;

	for(i = 0; i < TILE_CAPACITY; ++i){
		struct tv_Entity *e;
		struct Mesh *mesh;

		e = t->contents[i];
		if(e == NULL)
			break;

		mesh = (struct Mesh*)tv_EntityGetComponent(e, COMPONENT_MESH);
		if(mesh != NULL){
			struct Material *mat;
			mat = (struct Material*)tv_EntityGetComponent(e, COMPONENT_MATERIAL);
			tv_Draw(mesh, mat);
		}
	}
}

/* draw renders the map for the given camera. */
static void draw(struct Cam *cam)
{
	unsigned x, y;
	tv_Vector3 pos = cam->pos;

	x = (unsigned)pos.x;
	y = (unsigned)pos.y;

}

/* start registers a tile into the map (until removed) */
static void start()
{

}

/* update moves or deletes objects from the map as needed. */
static void update()
{

}

/* MapSystemAdd adds e to the map at position (x,y). */
void MapSystemAdd(unsigned x, unsigned y, struct tv_Entity *e)
{
	int i;
	for(i = 0; i < TILE_CAPACITY; ++i){
		if(worldMap[y][x].contents[i] == NULL)
			worldMap[y][x].contents[i] = e;
	}
}


/* MapSystemRemove removes e from the map tile (x,y). */
void MapSystemRemove(unsigned x, unsigned y, struct tv_Entity *e)
{
	int i;
	bool found;

	for(i = 0, found = false; i < TILE_CAPACITY; ++i){
		if(worldMap[y][x].contents[i] == e){
			worldMap[y][x].contents[i] = NULL;
			found = true;
			break;
		}
	}
	memmove(worldMap[y][x].contents + i, worldMap[y][x].contents + i + 1,
			(TILE_CAPACITY - i));
}

/* InitMapSystem initializes the system used to manage the world map. */
void InitMapSystem()
{
	struct tv_System sys = {
		.enabled = true,
		.Start = start,
		.Update = update,
		.Implements = NULL,
		.GlobalUpdate = NULL,
	};
	tv_RegisterSystem(&sys);
}

/* MapSystemLoad loads the given map data. */
void MapSystemLoad(uint16_t *map)
{
	unsigned row, col;
	unsigned size;

	col = map[0];
	col = map[1];
	size = map[2] * map[3];

	map += 2;
	for(i = 0; i < size; ++i){
		//MapSystemAdd();
	}
}
