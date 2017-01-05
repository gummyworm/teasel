#include "app_signals.h"
#include "debug.h"
#include "input.h"
#include "sigslot.h"
#include "systems/app_systems.h"
#include "systems/sys_console.h"
#include "systems/sys_fps_controller.h"
#include "systems/sys_gui.h"
#include "systems/sys_inventory.h"
#include "systems/sys_render.h"
#include <SDL2/SDL.h>
#include <engine.h>

void demo0();

/* button is called when a button is pressed. */
static void button(int button) {
	static uint32_t focused = SIGGROUP_FPS_CONTROLLER;

	switch (button) {
	case SDL_SCANCODE_F1:
		if (tv_SystemEnabled(SYSTEM_CONSOLE)) {
			tv_SystemDisable(SYSTEM_CONSOLE);
			focused = SIGGROUP_FPS_CONTROLLER;
			GDEACTIVATE(SIGGROUP_CONSOLE, ButtonDown);
			GACTIVATE(SIGGROUP_FPS_CONTROLLER, ButtonDown);
		} else {
			tv_SystemEnable(SYSTEM_CONSOLE);
			focused = SIGGROUP_CONSOLE;
			GDEACTIVATE(SIGGROUP_FPS_CONTROLLER, ButtonDown);
			GACTIVATE(SIGGROUP_CONSOLE, ButtonDown);
		}
		break;
	case SDL_SCANCODE_TAB:
		if (focused == SIGGROUP_FPS_CONTROLLER) {
			focused = SIGGROUP_CONSOLE;
			GDEACTIVATE(SIGGROUP_FPS_CONTROLLER, ButtonDown);
			GACTIVATE(SIGGROUP_CONSOLE, ButtonDown);
		} else {
			focused = SIGGROUP_FPS_CONTROLLER;
			GDEACTIVATE(SIGGROUP_CONSOLE, ButtonDown);
			GACTIVATE(SIGGROUP_FPS_CONTROLLER, ButtonDown);
		}
		break;
	default:
		break;
	}
}

/* input connects the relevant input signals for the game. */
static void initInput() {
	GDEACTIVATE(SIGGROUP_CONSOLE, ButtonDown);
	CONNECT(ButtonDown, button);
}

/* initSys initializes the systems required for the game. */
static void initSys() {
	InitRenderSystem();
	InitGUISystem();
	InitFpsControllerSystem();
	InitConsoleSystem();
	InitInventorySystem();
}

int main() {
	debug_puts("starting engine");
	tv_EngineInit();
	debug_puts("registering systems");
	initSys();
	initInput();

	debug_puts("starting scene");
	demo0();
	debug_puts("running engine");
	tv_EngineRun();

	debug_puts("done");
	return 0;
}
