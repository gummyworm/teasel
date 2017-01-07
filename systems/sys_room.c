#include "sys_room.h"
#include "app_systems.h"
#include "components/app_enum.h"
#include "system.h"

/* implements returns true if e is a room. */
static bool implements(struct tv_Entity *e) {
	return tv_EntityGetComponent(e, COMPONENT_ROOM) != NULL;
}

/* InitRoomSystem initializes the room system. */
void InitRoomSystem() {
	struct tv_System sys = {
	    .enabled = true,
	    .Start = NULL,
	    .Update = NULL,
	    .Implements = implements,
	    .GlobalUpdate = NULL,
	};
	tv_RegisterSystem(&sys, SYSTEM_ROOM);
}
