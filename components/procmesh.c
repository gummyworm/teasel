#include "procmesh.h"

/* Start initializes the ProcMesh component */
static void Start(struct tv_Component *c)
{
}

/* Size returns the size of the ProcMesh component */
static size_t Size()
{
  return sizeof(struct ProcMesh);
}

/* NewProcMesh creates a new ProcMesh component */
struct ProcMesh * NewProcMesh(int format, int n, 
    void (*rebuild)(struct ProcMesh*, int))
{
  struct ProcMesh *m;

  m = malloc(sizeof(struct ProcMesh));
  InitMesh((struct Mesh*)m, format, n);

  m->lod = 1;
  m->rebuild = rebuild;

  c = (tv_Component*)m;
  c->id = COMPONENT_MESH;
  c->Size = Size;
  c->Start = Start;
}
