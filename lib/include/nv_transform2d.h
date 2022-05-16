#ifndef _NV_TRANSFORM2D_H
#define _NV_TRANSFORM2D_H

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "nv_render2d_types.h"

void nv_transform2d(nv_mesh2d_t * meshes, size_t mesh_count) {
  float cos_tetha = 0;
  float sin_tetha = 0;
  for (int p = 0; p < mesh_count; p++) {
    nv_mesh2d_t mesh = meshes[p];
    if(mesh.rotation == 0) {
      float scaled_transition_x = mesh.scale.x * (1+mesh.position.x);
      float scaled_transition_y = mesh.scale.y * (1 + mesh.position.y);
      float vec[12] = {
          -mesh.scale.x + mesh.position.x, mesh.scale.y + mesh.position.y,
          -mesh.scale.x + mesh.position.x, -mesh.scale.y + mesh.position.y,
          mesh.scale.x + mesh.position.x, mesh.scale.y + mesh.position.y,
          -mesh.scale.x + mesh.position.x, -mesh.scale.y + mesh.position.y,
          mesh.scale.x + mesh.position.x, mesh.scale.y + mesh.position.y,
          mesh.scale.x + mesh.position.x, -mesh.scale.y + mesh.position.y,
      };
      memcpy(mesh.triangles, vec, sizeof(vec));
    }
  }
}

#endif
