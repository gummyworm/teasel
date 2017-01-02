#ifndef COMPONENT_AI_H
#define COMPONENT_AI_H

#include "entity.h"

enum AIBehavior {
	AI_FOLLOW,
	AI_ATTACK,
};

struct AIFollowInfo {
	float speed;
};

struct AI {
	enum AIBehavior behavior;
	struct tv_Entity *target;
	union {
		struct AIFollowInfo follow;
	} info;
};

#endif
