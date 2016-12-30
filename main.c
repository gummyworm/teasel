#include "debug.h"
#include "systems/sys_fps_controller.h"
#include "systems/sys_gui.h"
#include "systems/sys_render.h"
#include <engine.h>

void demo0();

/* initSys initializes the systems required for the game. */
static void initSys() {
	InitRenderSystem();
	InitGUISystem();
	InitFpsControllerSystem();
}

int main() {
	debug_puts("starting engine");
	tv_EngineInit();
	debug_puts("registering systems");
	initSys();

	debug_puts("starting scene");
	demo0();
	debug_puts("running engine");
	tv_EngineRun();

	debug_puts("done");
	return 0;
}
