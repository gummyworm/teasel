#include "sys_maingui.h"
#include "app_systems.h"
#include "system.h"
#include <draw.h>

/* gui is a struct that contains the data used to render the main GUI. */
static struct gui {};

/* globalUpdate updates the main GUI. */
static void globalUpdate(struct tv_Entity *e) {}

/* NewMainGUISystem creates a new system for rendering hte GUI */
void InitMainGUISystem() {
	struct tv_System sys = {
	    .enabled = true,
	    .Start = NULL,
	    .Update = NULL,
	    .Implements = NULL,
	    .GlobalUpdate = globalUpdate,
	};
	tv_RegisterSystem(&sys, SYSTEM_MAINGUI);
}
