#include "entity.h"
#include "system.h"

#include "components/app_enum.h"
#include "components/battlestats.h"
#include "components/battleattack.h"

#include "sys_config.h"
#include "sys_battle.h"

/* battlers contains all the active combatants managed by the battle system. */
static struct{
	struct tv_Entity *e;
	struct BattleStats *stats;
}battlers[MAX_BATTLERS];

/* implements returns true if the entity has a BattleStats component. */
static bool implements(struct tv_Entity *e)
{
	return tv_EntityGetComponent(e, COMPONENT_BATTLESTATS) != NULL;
}

/* update updates the stats of any battlers. */
static void update(struct tv_Entity *e)
{
	unsigned i;
	for(i = 0; i < MAX_BATTLERS; ++i){
		if(battlers[i].e != NULL){
			if(battlers[i].stats->hp <= 0){
				/*TODO: destroy entity */
				break;
			}
		}
	}
}

/* InitBattleSystem initializes the battle system. */
void InitBattleSystem()
{
	struct tv_System sys = {
		.enabled = true,
		.Start = NULL,
		.Update = update,
		.Implements = implements,
		.GlobalUpdate = NULL,
	};
	tv_RegisterSystem(&sys);
}

/* BattleDamage inflicts damage on target. */
static void BattleDamage(struct tv_Entity *target, unsigned damage)
{
	unsigned i;
	for(i = 0; i < MAX_BATTLERS; ++i){
		if(battlers[i].e == target){
			uint16_t dmg;
		       	dmg = damage - battlers[i].stats->def;
			battlers[i].stats->hp -= dmg;
		}
	}
}

/* BattleAttack attacks target with atk. */
static void BattleAttack(struct tv_Entity *target, struct BattleAttack *atk)
{
	struct BattleStats *stats;

	stats = tv_EntityGetComponent(target, COMPONENT_BATTLESTATS);
	switch(atk->effect){
		case MOVE_DMGATTR:
			break;
		default:
			break;
	}
	if(stats != NULL){
		BattleDamage(target, atk->dmg);
	}
}
