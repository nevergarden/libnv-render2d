#ifndef _NV_RENDER2D_H
#define _NV_RENDER2D_H
#include <stdlib.h>
#include <GL/gl.h>

typedef struct nv_gl_shader_s {
  const GLchar * vertex_shader;
  GLint vertex_shader_length;

  const GLchar * fragment_shader;
  GLint fragment_shader_length;
} nv_gl_raw_shader_t;

GLuint nv_gl_compile_generic_shader();
GLuint nv_gl_compile_shader(nv_gl_raw_shader_t shader);
void nv_gl_set_clear_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
void nv_gl_render_clear();
void nv_gl_init();

void init_quad(GLuint * quad_vbo, GLuint * quad_ibo);
void draw_quad(GLuint shader, GLuint vbo, GLuint ibo);
#endif
