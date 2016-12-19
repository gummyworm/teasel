#include "components/app_enum.h"
#include "components/cam.h"
#include "components/enum.h"
#include "components/material.h"
#include "components/mesh.h"
#include "components/motionstats.h"
#include "components/transform.h"
#include "debug.h"
#include "entity.h"


enum {
	MAP_W = 8,
	MAP_H = 8,
};


/* tilemap is a map of the tiles contained in this scene. */
static uint8_t tilemap[MAP_W * MAP_H] = {
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1
};

/* player spawns the player entity for the scene. */
static struct tv_Entity * player()
{
	struct Cam cam;
	struct Transform transform;
	struct MotionStats mstats;

	cam = NewCam();
	transform = NewTransform(tv_Vector3Zero, tv_Vector4Zero, tv_Vector3One);
	mstats = NewMotionStats(1,1,1,1,1);

	debug_puts("spawning player");
	return tv_EntityNew(3,
		COMPONENT_TRANSFORM, &transform,
		COMPONENT_CAM, &cam,
		COMPONENT_MOTIONSTATS, &mstats);
}

/* tiles spawns the tile entities for the scene. */
static struct tv_Entity * tiles()
{
	struct Material material;
	struct Mesh mesh;
	uint8_t x, y;

	mesh = MeshNewQuad();
	material = NewMaterial(0xffff,0xffff,0xffff,0xffff);
	for(y = 0; y < MAP_H; ++y){
		for(x = 0; x < MAP_W; ++x){
			if(tilemap[y*MAP_W + x] == 1){
				struct Transform transform;
				transform = NewTransform(
						(tv_Vector3){x,0,y-4},
						(tv_Quaternion){90.0f,0,0},
						tv_Vector3One);
				debug_puts("spawning tile");
				tv_EntityNew(3,
					COMPONENT_TRANSFORM, &transform,
					COMPONENT_MESH, &mesh,
					COMPONENT_MATERIAL, &material);
			}
		}
	}
	return NULL;
}

/* demo0 creates the demo0 scene. */
void demo0()
{
	struct tv_Entity *p, *t;

	p = player();
	t = tiles();

	FpsControllerPossess(p);
}
