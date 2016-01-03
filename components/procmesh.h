#ifndef PROCMESH_H
#define PROCMESH_H

#include <components/mesh.h>

/**
 * ProcMesh is a component that extends mesh data with facilities for
 * procedurally building meshes.
 */
struct ProcMesh
{
  struct tv_Mesh mesh;
  int lod;
  void (*rebuild)(struct ProcMesh*, int);
}

struct ProcMesh * NewProcMesh(int, int, void (*rebuild)(struct ProcMesh*, int));

#endif
