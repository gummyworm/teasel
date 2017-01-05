#include "sys_inventory.h"
#include "app_systems.h"
#include "components/app_enum.h"
#include "system.h"

static bool implements(struct tv_Entity *e) {
	return tv_EntityGetComponent(e, COMPONENT_INVENTORY);
}

static void update() {}

/* InitFpsController initializes a first-person-? controller. */
void InitInventorySystem() {
	struct tv_System sys = {
	    .enabled = true,
	    .Start = NULL,
	    .Update = update,
	    .Implements = implements,
	    .GlobalUpdate = NULL,
	};
	tv_RegisterSystem(&sys, SYSTEM_INVENTORY);
}
