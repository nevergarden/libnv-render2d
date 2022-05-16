#ifndef NV_RENDER2D_SHADER_H
#define NV_RENDER2D_SHADER_H

#include "glad/glad.h"
#include "nv_render2d_types.h"

#include <string.h>

#define _NV_RENDER2D_SHADER_IMPL
#ifdef _NV_RENDER2D_SHADER_IMPL
GLenum compile_vertex_shader(nv_gl_render2d_program_t * self) {
  if(self->vertex_shader_program != 0) {
    glad_glDetachShader(self->shader_program, self->vertex_shader_program);
    glad_glDeleteShader(self->vertex_shader_program);
    self->flags |= (SHADER_DIRTY | SHADER_MISS_VERTEX_SHADER);
  }

  self->vertex_shader_program = glad_glCreateShader(GL_VERTEX_SHADER);
  if(self->vertex_shader_program == 0) {
    return glad_glGetError();
  }

  const GLchar * string = self->vertex_shader_string;
  const GLint length = self->vertex_shader_length; 
  glad_glShaderSource(self->vertex_shader_program, 1, &string, &length);
  glad_glCompileShader(self->vertex_shader_program);
  if(glad_glGetError())
    return 0;
  glad_glAttachShader(self->shader_program, self->vertex_shader_program);
  if(glad_glGetError())
    return 0;
  self->flags &= ~(SHADER_MISS_VERTEX_SHADER);
  return 1;
}

GLenum compile_fragment_shader(nv_gl_render2d_program_t * self) {
  if(self->fragment_shader_program != 0) {
    glad_glDetachShader(self->shader_program, self->fragment_shader_program);
    glad_glDeleteShader(self->fragment_shader_program);
    self->flags |= (SHADER_DIRTY | SHADER_MISS_FRAGMENT_SHADER);
  }

  self->fragment_shader_program = glad_glCreateShader(GL_FRAGMENT_SHADER);
  if(self->fragment_shader_program == 0) {
    return glad_glGetError();
  }

  const GLchar * string = self->fragment_shader_string;
  const GLint length = self->fragment_shader_length; 
  glad_glShaderSource(self->fragment_shader_program, 1, &string, &length);
  glad_glCompileShader(self->fragment_shader_program);
  if(glad_glGetError())
    return 0;
  glad_glAttachShader(self->shader_program, self->fragment_shader_program);
  if(glad_glGetError())
    return 0;
  self->flags &= ~(SHADER_MISS_FRAGMENT_SHADER);
  return 1;
}

GLenum link_shaders(nv_gl_render2d_program_t * self) {
  if(self->flags & (SHADER_MISS_VERTEX_SHADER | SHADER_MISS_FRAGMENT_SHADER))
    return 0;

  glad_glLinkProgram(self->shader_program);
  if(glad_glGetError())
    return 0;

  self->flags &= ~(SHADER_DIRTY);
  return 1;
}

GLuint bind_shader(nv_gl_render2d_program_t * self) {
  if(self->flags & SHADER_DIRTY)
    return 0;
  glad_glUseProgram(self->shader_program);
  self->flags |= SHADER_IN_USE;
  return self->shader_program;
}

void unbind_shader(nv_gl_render2d_program_t * self) {
  if(self->flags & SHADER_IN_USE)
    return;
  glad_glUseProgram(0);
  self->flags &= ~(SHADER_IN_USE);
}
#endif

static const char * nv_generic_quad_shader_vs = "#version 330 core\n"
"layout(location=0) in vec2 aPos\n"
"void main() { gl_Position = vec4(aPos.x, aPos.y, 0,1); }";

static const char * nv_generic_quad_shader_fs = "#version 330 core\n"
"out vec4 gl_Color\n"
"void main() { gl_Color = vec4(1,1,1,1); }";

void nv_gl_create_shader_program(nv_gl_render2d_program_t * program, const char * vertex_shader, const char * fragment_shader) {
  program->flags = 0;
  program->vertex_shader_program = 0;
  program->fragment_shader_program = 0;
  program->flags |= (SHADER_DIRTY | SHADER_MISS_VERTEX_SHADER | SHADER_MISS_FRAGMENT_SHADER);
  program->vertex_shader_string = vertex_shader;
  program->vertex_shader_length = strlen(vertex_shader);
  program->fragment_shader_string = fragment_shader;
  program->fragment_shader_length = strlen(fragment_shader);
  program->compile_vertex_shader = compile_vertex_shader;
  program->compile_fragment_shader = compile_fragment_shader;
  program->link_shaders = link_shaders;
  program->bind = bind_shader;
  program->unbind = unbind_shader;

  program->shader_program = glad_glCreateProgram();
  program->compile_vertex_shader(program);
  program->compile_fragment_shader(program);
  program->link_shaders(program);
}

#undef _NV_RENDER2D_SHADER_IMPL

#endif
