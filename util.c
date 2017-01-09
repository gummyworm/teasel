#include "util.h"
#include <stdlib.h>

#define MAX_VERTICES 10000

/* setVertices sets the vertices for the mesh. */
static void setVertices() {}

/* LoadPicAsMesh returns a mesh component using the picture from filename. */
struct Mesh LoadPicAsMesh(const char *filename) {
	static uint8_t vertices[MAX_VERTICES]; // XXX
	char line[256];
	FILE *f;
	uint8_t *pv;
	float x, y, z;
	struct Mesh mesh;

	f = fopen(filename, "r");
	pv = vertices;
	while (fgets(line, sizeof(line), f) == NULL) {
		if (sscanf(line, "v %f, %f, %f", &x, &y, &z) == 3) {
			*pv++ = (uint8_t)(x * 255.0f);
			*pv++ = (uint8_t)(y * 255.0f);
			*pv++ = (uint8_t)(z * 255.0f);
			*pv++ = (uint8_t)(255.0f);
		}
	}
	fclose(f);

	mesh = NewMesh(pv - vertices, 2);

	// TODO: MeshSetVertices after component's init is called.

	return mesh;
}
