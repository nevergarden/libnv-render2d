#ifndef _NV_RENDER2D_TYPES_H
#define _NV_RENDER2D_TYPES_H

typedef struct nv_fpoint2d_s {
  float x;
  float y;
} nv_fpoint2d_t;

typedef struct nv_mesh2d_s {
  nv_fpoint2d_t position;
  nv_fpoint2d_t scale;
  float rotation;
} nv_mesh2d_t;

#endif
