#ifndef ROOM_H
#define ROOM_H

#include "entity.h"

#define ROOM_MAX_ENTITIES 64
#define ROOM_MAX_EXITS 16

enum RoomDirection {
	ROOM_NORTH,
	ROOM_SOUTH,
	ROOM_WEST,
	ROOM_EAST,
	ROOM_UP,
	ROOM_DOWN,
	ROOM_NUM_DIRECTIONS
};

struct Room {
	TV_COMPONENT
	const char *name;
	struct tv_Entity *entities[ROOM_MAX_ENTITIES];
	void (*exits[ROOM_NUM_DIRECTIONS])();
};

struct Room NewRoom(const char *);
struct tv_Entity *RoomRemove(struct Room *, struct tv_Entity *);
struct tv_Entity *RoomAdd(struct Room *, struct tv_Entity *);
struct tv_Entity *RoomGet(struct Room *, const char *);
void RoomConnect(struct Room *, void (*)(), enum RoomDirection);

#endif
