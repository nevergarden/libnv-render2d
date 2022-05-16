#ifndef _NV_RENDER2D_H
#define _NV_RENDER2D_H
#include "nv_render2d_types.h"
#include <stdlib.h>
#include <GL/gl.h>

static GLuint current_array_buffer_bind = 0;

typedef enum nv_gl_render2d_draw_frequency {
  STREAM = GL_STREAM_DRAW,
  STATIC = GL_STATIC_DRAW,
  DYNAMIC = GL_DYNAMIC_DRAW
} nv_gl_render2d_draw_frequency;

typedef struct nv_gl_f_vertex_buffer_s {
  nv_gl_render2d_program_t * shader_program;
  GLuint buffer;
  uint32_t buffer_count;
  nv_gl_render2d_draw_frequency draw_fequency;
  void (*bind)(struct nv_gl_f_vertex_buffer_s * self);
  void (*draw)(struct nv_gl_f_vertex_buffer_s * self);
  void (*unbind)(struct nv_gl_f_vertex_buffer_s * self);
} nv_gl_f_vertex_buffer_t;

void __f_vertex_buffer_bind(nv_gl_f_vertex_buffer_t * self) {
  if(current_array_buffer_bind != self->buffer) {
    glad_glBindBuffer(GL_ARRAY_BUFFER, self->buffer);
    current_array_buffer_bind = self->buffer;
  }
}

void __f_vertex_buffer_unbind(nv_gl_f_vertex_buffer_t * self) {
  if(current_array_buffer_bind != 0) {
    glad_glBindBuffer(GL_ARRAY_BUFFER, 0);
    current_array_buffer_bind = 0;
  }
}

void nv_gl_create_f_vertex_array(
    nv_gl_f_vertex_buffer_t* buffer,
    nv_gl_render2d_program_t * program,
    nv_gl_render2d_draw_frequency draw_fequency,
    uint32_t count) {
  buffer->shader_program = program;
  buffer->buffer_count = count;
  buffer->draw_fequency = draw_fequency;
  buffer->bind = __f_vertex_buffer_bind;
  buffer->unbind = __f_vertex_buffer_unbind;
  glad_glGenBuffers(1, &buffer->buffer);
  buffer->bind(buffer);
  glad_glBufferData(GL_ARRAY_BUFFER, buffer->buffer_count*12*sizeof(float), NULL, buffer->draw_fequency);
}

void nv_gl_set_triangle_f_vertex_array(nv_gl_f_vertex_buffer_t * buffer, uint32_t offset, const float * data) {
  buffer->bind(buffer);
  glad_glBufferSubData(GL_ARRAY_BUFFER, offset*12*sizeof(float), 12*sizeof(float), data);
}

void nv_gl_draw_triangle_from_f_vertex_array(nv_gl_f_vertex_buffer_t * buffer) {
  buffer->shader_program->bind(buffer->shader_program);
  glad_glBindBuffer(GL_ARRAY_BUFFER, buffer->buffer);
  // pos attribute
  glad_glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
  glad_glEnableVertexAttribArray(0);
  glad_glDrawArrays(GL_TRIANGLES, 0, 12*buffer->buffer_count*sizeof(float));
  glad_glDisableVertexAttribArray(0);
  buffer->shader_program->unbind(buffer->shader_program);
}

void nv_gl_set_clear_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
void nv_gl_render_clear();
void nv_gl_init();
#endif
