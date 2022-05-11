#include <nv_render2d.h>
#include "glad/glad.h"
#include <GL/gl.h>

void init_quad(GLuint * quad_vbo, GLuint * quad_ibo) {
  float vec[] = {
    -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f, 0.0f, 1.0f
  };

  unsigned int ind[] = {
    0,1,2,
    0,2,3
  };

  glad_glGenBuffers(1, quad_vbo);
  glad_glBindBuffer(GL_ARRAY_BUFFER, *quad_vbo);
  glad_glBufferData(GL_ARRAY_BUFFER, sizeof(vec), vec, GL_STATIC_DRAW);

  glad_glGenBuffers(1, quad_ibo);
  glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *quad_ibo);
  glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);
}
