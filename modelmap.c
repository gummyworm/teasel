#include "debug.h"

#include "components/material.h"
#include "components/mesh.h"

#include "modelmap.h"

static struct {
	struct Mesh *mesh;
	struct Material *material;
}models[NUM_MODELS];

/* NewModel creates the model (mesh + material) that corresponds to id */
void NewModel(uint16_t id, struct Mesh *mesh, struct Material *mat)
{
	if(id > NUM_MODELS){
		debug_printf("warning: invalid model ID %d\n", id);
		return;
	}
	mesh = models[id].mesh;
	mat = models[id].material;
}
