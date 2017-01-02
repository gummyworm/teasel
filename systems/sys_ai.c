#include "sys_ai.h"
#include "components/ai.h"
#include "components/app_enum.h"
#include "components/transform.h"
#include "globals.h"
#include "vector.h"

/* moveTo moves e toward target at the given speed. */
static void moveTo(struct tv_Entity *e, struct tv_Entity *target, float speed) {
	struct Transform *t, *to;
	struct tv_Vector3 dpos;
	float d;

	d = tv_DeltaTime * speed;
	t = (struct Transform *)tv_EntityGetComponent(e, COMPONENT_TRANSFORM);
	to = (struct Transform *)tv_EntityGetComponent(target,
	                                               COMPONENT_TRANSFORM);
	tv_Vector3Sub(to->pos, t->pos, &dpos);
	tv_Vector3Normalize(dpos, &dpos);
	tv_Vector3Scale(&dpos, d);

	if (tv_Vector3Mag(&dpos) < d) {
		t->pos = to->pos;
	} else {
		tv_Vector3Add(t->pos, dpos, &to->pos);
	}
}

static void update(struct tv_Entity *e) {
	struct AI *ai;
	ai = (struct AI *)tv_EntityGetComponent(e, COMPONENT_AI);

	switch (ai->behavior) {
	case AI_FOLLOW:
	case AI_ATTACK:
		moveTo(e, ai->target, ai->info.follow.speed);
		break;
	default:
		break;
	}
}

void InitAISystem() {
	struct tv_System sys = {
	    .enabled = true,
	    .Start = NULL,
	    .Update = update,
	    .Implements = NULL,
	    .GlobalUpdate = NULL,
	};

	tv_RegisterSystem(&sys);
}
