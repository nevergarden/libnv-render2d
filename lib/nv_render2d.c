#include "glad/glad.h"
#include "nv_render2d_types.h"
#include <nv_render2d.h>
#include <nv_render2d_shader.h>
#include <string.h>

void nv_gl_set_clear_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
  glad_glClearColor(r,g,b,a);
}

void nv_gl_render_clear() {
  glad_glClear(GL_COLOR_BUFFER_BIT);
}

void nv_gl_init() {
  gladLoadGL();
}

void init_quad(GLuint * quad_vbo) {
  float vec[] = {
    -1.0f,  1.0f,
    -1.0f, -1.0f,
     1.0f,  1.0f,
    -1.0f, -1.0f,
     1.0f,  1.0f,
     1.0f, -1.0f,
  };

  glad_glGenBuffers(1, quad_vbo);
  glad_glBindBuffer(GL_ARRAY_BUFFER, *quad_vbo);
  glad_glBufferData(GL_ARRAY_BUFFER, 2*sizeof(vec), vec, GL_STATIC_DRAW);
}

void draw_quad(nv_gl_render2d_program_t * program, GLuint vbo) {
  program->bind(program);
  glad_glBindBuffer(GL_ARRAY_BUFFER, vbo);
  
  // pos
  glad_glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
  glad_glEnableVertexAttribArray(0);

  glad_glDrawArrays(GL_TRIANGLES, 0, 24*sizeof(float));
  glad_glDisableVertexAttribArray(0);
  program->unbind(program);
}
