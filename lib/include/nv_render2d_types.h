#ifndef _NV_RENDER2D_TYPES_H
#define _NV_RENDER2D_TYPES_H

#include <stdlib.h>
#include <glad/glad.h>
#include <GL/gl.h>

typedef struct nv_fpoint2d_s {
  float x;
  float y;
} nv_fpoint2d_t;

typedef struct nv_mesh2d_s {
  nv_fpoint2d_t position;
  nv_fpoint2d_t scale;
  float rotation;
  float * triangles;
} nv_mesh2d_t;

// NV SHADER ------------------------
typedef enum nv_gl_shader_flags_s {
  SHADER_DIRTY = 0b1,
  SHADER_MISS_VERTEX_SHADER = 0b10,
  SHADER_MISS_FRAGMENT_SHADER = 0b100,
  SHADER_IN_USE = 0b1000,
} nv_gl_shader_flags;

typedef struct nv_gl_render2d_program_s {
  // Shader Data
  const char * vertex_shader_string;
  size_t vertex_shader_length;
  const char * fragment_shader_string;
  size_t fragment_shader_length;

  // Shader Program
  nv_gl_shader_flags flags;
  GLuint vertex_shader_program;
  GLuint fragment_shader_program;
  GLuint shader_program;

  GLenum (*compile_vertex_shader)(struct nv_gl_render2d_program_s * self);
  GLenum (*compile_fragment_shader)(struct nv_gl_render2d_program_s * self);
  GLenum (*link_shaders)(struct nv_gl_render2d_program_s * self);
  GLuint (*bind)(struct nv_gl_render2d_program_s * self);
  void (*unbind)(struct nv_gl_render2d_program_s * self);
} nv_gl_render2d_program_t;
// --------------------------------

#endif
