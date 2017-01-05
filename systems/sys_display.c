#include "sys_display.h"
#include "app_systems.h"
#include <stdbool.h>

static void globalUpdate() {}

/* layoutDisplay arranges the display for the desired rendering layout. */
/* TODO: */
static void layoutDisplay() {}

void InitDisplaySystem() {
	struct tv_System sys = {
	    .enabled = true,
	    .Start = NULL,
	    .Update = NULL,
	    .Implements = NULL,
	    .GlobalUpdate = globalUpdate,
	};
	tv_RegisterSystem(&sys, SYSTEM_DISPLAY);
}
