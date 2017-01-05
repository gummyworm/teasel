#include "sys_fps_controller.h"
#include "app_signals.h"
#include "app_systems.h"
#include "components/app_enum.h"
#include "components/enum.h"
#include "components/motionstats.h"
#include "components/transform.h"
#include "debug.h"
#include "input.h"
#include "matrix.h"
#include "sigslot.h"
#include "system.h"
#include <SDL2/SDL.h> //XXX
#include <math.h>

struct tv_Entity *possessed;
static float rot;
static tv_Vector3 vel;

/* moveX rotates the possessed entity left/right. */
static void moveX(int x) {
	struct MotionStats *m;
	m = (struct MotionStats *)tv_EntityGetComponent(possessed,
	                                                COMPONENT_MOTIONSTATS);
	if (m == NULL)
		return;

	rot -= .0015f * (float)x * (float)(m->turn);

	if (rot >= TWO_PI)
		rot -= TWO_PI;
	else if (rot <= 0)
		rot = TWO_PI - rot;
}

/* moveX moves the possessed entity forward/backward. */
static void moveY(int y) {
	uint16_t scale;
	struct MotionStats *m;
	m = (struct MotionStats *)tv_EntityGetComponent(possessed,
	                                                COMPONENT_MOTIONSTATS);
	if (m == NULL)
		return;

	if (y > 0)
		scale = m->forward;
	else
		scale = m->backpedal;

	vel.z = cos(rot) * -0.1f * y * scale;
	vel.x = sin(rot) * -0.1f * y * scale;
}

/* move dispatches to the given axis handler. */
static void move(int axis, int amt) {
	if (possessed == NULL)
		return;
	switch (axis) {
	case TV_INPUT_AXIS0:
		moveX(amt);
		break;
	case TV_INPUT_AXIS1:
		// moveY(amt);
		break;
	}
}

/* button is called when a button is pressed. */
static void button(int button) {
	switch (button) {
	case SDL_SCANCODE_W:
		moveY(1);
		break;
	case SDL_SCANCODE_S:
		moveY(-1);
		break;
	}
	// t->pos.z -= vel; // dir.y;
}

/* button is called when a button is released. */
static void buttonUp(int button) {
	switch (button) {
	case SDL_SCANCODE_W:
	case SDL_SCANCODE_S:
		vel.x = 0.0f;
		vel.z = 0.0f;
		break;
	}
	// t->pos.z -= vel; // dir.y;
}

/* globalUpdate moves the possessed entity according to input. */
static void globalUpdate() {
	struct Transform *t;

	if (possessed == NULL)
		return;
	t = (struct Transform *)tv_EntityGetComponent(possessed,
	                                              COMPONENT_TRANSFORM);
	if (t != NULL) {
		t->rot.y = rot;
		tv_Vector3Add(t->pos, vel, &t->pos);
	}
}

/* InitFpsController initializes a first-person-? controller. */
void InitFpsControllerSystem() {
	struct tv_System sys = {
	    .enabled = true,
	    .Start = NULL,
	    .Update = NULL,
	    .Implements = NULL,
	    .GlobalUpdate = globalUpdate,
	};
	tv_RegisterSystem(&sys, SYSTEM_FPS_CONTROLLER);

	GCONNECT(SIGGROUP_FPS_CONTROLLER, AxisMoved, move);
	GCONNECT(SIGGROUP_FPS_CONTROLLER, ButtonDown, button);
	GCONNECT(SIGGROUP_FPS_CONTROLLER, ButtonUp, buttonUp);
}

/* FpsControllerPossess possesses e. */
void FpsControllerPossess(struct tv_Entity *e) { possessed = e; }
