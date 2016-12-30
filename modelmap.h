#ifndef MODELMAP_H
#define MODELMAP_H

enum {
	WALL_CUBE,
	NUM_MODELS,
};

void NewModel(uint16_t, struct Mesh *, struct Material *);

#endif
