#include "entity.h"
#include "system.h"

#include "sys_config.h"
#include "sys_move.h"

#include "components/app_enum.h"
#include "components/enum.h"
#include "components/motionstats.h"

/* movers are all the detected entities capable of motion. */
struct tv_Entity *movers[MAX_MOVERS];

/* update moves all detected in-motion entities. */
void globalUpdate() {
	unsigned i;
	for (i = 0; i < MAX_MOVERS; ++i) {
		struct Transform *t;
		struct MotionStats *ms;
		struct tv_Entity *e;

		e = movers[i];
		t = (struct Transform *)tv_EntityGetComponent(
		    e, COMPONENT_TRANSFORM);
		ms = (struct MotionStats *)tv_EntityGetComponent(
		    e, COMPONENT_MOTIONSTATS);
		/* TODO: update transform according to ms->velX, etc. */
	}
}

/* InitMoveSystem intializes the system responsible for moving entities. */
void InitMoveSystem() {
	struct tv_System sys = {
	    .enabled = true,
	    .Start = NULL,
	    .Update = NULL,
	    .Implements = NULL,
	    .GlobalUpdate = globalUpdate,
	};
	tv_RegisterSystem(&sys);
}
