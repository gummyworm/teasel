#include "room.h"
#include "entity.h"
#include <string.h>

/* NewRoom creates and returns a new room named name. */
struct Room NewRoom(const char *name) {
	struct Room r = {
	    .C = {.size = sizeof(struct Room)},
	    .name = name,
	    .entities = {NULL},
	    .exits = {NULL},
	};
	return r;
}

/* RoomRemove removes e from room and returns the entity that was removed. */
struct tv_Entity *RoomRemove(struct Room *room, struct tv_Entity *e) {
	unsigned i;

	for (i = 0; i < ROOM_MAX_ENTITIES; ++i) {
		if (room->entities[i] == e) {
			room->entities[i] = NULL;
			return e;
		}
	}

	return NULL;
}

/* RoomAdd adds e to room and returns the entity that was added. */
struct tv_Entity *RoomAdd(struct Room *room, struct tv_Entity *e) {
	unsigned i;

	for (i = 0; i < ROOM_MAX_ENTITIES; ++i) {
		if (room->entities[i] == NULL) {
			room->entities[i] = e;
			return e;
		}
	}

	return NULL;
}

/* RoomGet returns the the entity named name if it exists in room */
struct tv_Entity *RoomGet(struct Room *room, const char *name) {
	unsigned i;

	for (i = 0; i < ROOM_MAX_ENTITIES; ++i) {
		if (strcmp(room->entities[i]->name, name) == 0) {
			return room->entities[i];
		}
	}

	return NULL;
}

/* RoomConnect connects the exit via dir to onTraverse. */
void RoomConnect(struct Room *r1, void (*onTraverse)(),
                 enum RoomDirection dir) {
	r1->exits[dir] = onTraverse;
}
