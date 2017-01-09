#include "components/app_enum.h"
#include "components/cam.h"
#include "components/console.h"
#include "components/description.h"
#include "components/enum.h"
#include "components/gui.h"
#include "components/inventory.h"
#include "components/material.h"
#include "components/mesh.h"
#include "components/motionstats.h"
#include "components/transform.h"
#include "debug.h"
#include "entity.h"
#include "systems/sys_fps_controller.h"
#include "systems/sys_render.h"

enum { MAP_W = 8,
       MAP_H = 8,
};

/* tilemap is a map of the tiles contained in this scene. */
static uint8_t tilemap[MAP_W * MAP_H] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
    0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
    0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1};

/* player spawns the player entity for the scene. */
static struct tv_Entity *player() {
	struct Cam cam;
	struct Transform transform;
	struct MotionStats mstats;
	struct Console console;
	struct Inventory inventory;

	cam = NewCam();
	transform = NewTransform(tv_Vector3Zero, tv_Vector4Zero, tv_Vector3One);
	mstats = NewMotionStats(1, 1, 1, 1, 1);
	console = NewConsole();
	inventory = NewInventory();

	debug_puts("spawning player");
	return tv_EntityNew(5, COMPONENT_TRANSFORM, &transform, COMPONENT_CAM,
	                    &cam, COMPONENT_MOTIONSTATS, &mstats,
	                    COMPONENT_CONSOLE, &console, COMPONENT_INVENTORY,
	                    &inventory);
}

/* textTest spawns the text test entity. */
static struct tv_Entity *textTest() {
	struct Transform transform;
	struct GUIText guiText;
	transform = NewTransform(tv_Vector3Zero, tv_Vector4Zero, tv_Vector3One);
	debug_puts("spawning gui text");
	guiText = NewGUIText("hello world");
	return tv_EntityNew(2, COMPONENT_TRANSFORM, &transform,
	                    COMPONENT_GUITEXT, &guiText);
}

/* sword spawns the sword entity */
static struct tv_Entity *sword() {
	struct Transform transform;
	struct Mesh mesh;
	struct Description desc;
	struct tv_Entity *s;

	struct Mesh *m;

	transform = NewTransform((tv_Vector3){0.5f, 1.0f, 1.5f}, tv_Vector4Zero,
	                         tv_Vector3One);
	mesh = MeshNewQuad();
	desc = NewDescription(NULL, "a sharp, pointed blade");
	s = tv_EntityNew(3, COMPONENT_TRANSFORM, &transform, COMPONENT_MESH,
	                 &mesh, COMPONENT_DESCRIPTION, &desc);
	tv_EntityRename(s, "SWORD");

	m = (struct Mesh *)tv_EntityGetComponent(s, COMPONENT_MESH);
	MeshColor(m, 0x00, 0x20, 0xff, 0xff);

	return s;
}

/* star spawns the star entity. */
static struct tv_Entity *star() {
	struct tv_Entity *e;
	struct Transform transform;
	struct Mesh mesh;
	struct Material material;

	debug_puts("spawning star");
	transform = NewTransform(tv_Vector3One, tv_Vector4Zero, tv_Vector3One);
	mesh = MeshNewObj("res/star.obj");
	material = NewMaterial(0xffff, 0xffff, 0xffff, 0xffff);

	e = tv_EntityNew(3, COMPONENT_TRANSFORM, transform, COMPONENT_MESH,
	                 mesh, COMPONENT_MATERIAL, material);

	return e;
}

/* tiles spawns the tile entities for the scene. */
static struct tv_Entity *tiles() {
	struct Material material;
	struct Mesh mesh;
	uint8_t x, y;

	mesh = MeshNewQuad();
	material = NewMaterial(0xffff, 0xffff, 0xffff, 0xffff);
	for (y = 0; y < MAP_H; ++y) {
		for (x = 0; x < MAP_W; ++x) {
			struct tv_Entity *e;
			struct Mesh *m;

			if (tilemap[y * MAP_W + x] == 1) {
				struct Transform transform;
				transform = NewTransform(
				    (tv_Vector3){x, 0.0f, y - 4},
				    (tv_Quaternion){90.0f, 0, 0, 0},
				    tv_Vector3One);
				e = tv_EntityNew(3, COMPONENT_TRANSFORM,
				                 &transform, COMPONENT_MESH,
				                 &mesh, COMPONENT_MATERIAL,
				                 &material);

				m = (struct Mesh *)tv_EntityGetComponent(
				    e, COMPONENT_MESH);
				MeshColor(m, 100 + x * 8, y * 8, x * y, 0xff);
			}
		}
	}
	return NULL;
}

/* demo0 creates the demo0 scene. */
void demo0() {
	static struct tv_Entity *p, *t, *txt, *sw, *st;

	p = player();
	t = tiles();
	txt = textTest();
	sw = sword();
	st = star();

	FpsControllerPossess(p);
	RenderSetEye(
	    (struct Transform *)tv_EntityGetComponent(p, COMPONENT_TRANSFORM));
}
