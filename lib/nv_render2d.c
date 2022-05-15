#include "glad/glad.h"
#include <nv_render2d.h>
#include <string.h>

static const char * nv_generic_quad_shader_vs = "#version 330 core\n"
"layout(location=0) in vec2 aPos\n"
"void main() { gl_Position = vec4(aPos.x, aPos.y, 0,1); }";

static const char * nv_generic_quad_shader_fs = "#version 330 core\n"
"out vec4 gl_Color\n"
"void main() { gl_Color = vec4(1,1,1,1); }";


GLuint nv_gl_compile_generic_shader() {
  nv_gl_raw_shader_t generic = {
    nv_generic_quad_shader_vs,
    strlen(nv_generic_quad_shader_vs),
    nv_generic_quad_shader_fs,
    strlen(nv_generic_quad_shader_fs)
  };
  return nv_gl_compile_shader(generic);
}

GLuint nv_gl_compile_shader(nv_gl_raw_shader_t shader) {
  GLuint shader_program;
  GLuint vs_shader_obj = glad_glCreateShader(GL_VERTEX_SHADER);
  glad_glShaderSource(vs_shader_obj, 1, &shader.vertex_shader, &shader.vertex_shader_length);
  glad_glCompileShader(vs_shader_obj);
  glad_glAttachShader(shader_program, vs_shader_obj);

  GLuint fs_shader_obj = glad_glCreateShader(GL_FRAGMENT_SHADER);
  glad_glShaderSource(fs_shader_obj, 1, &shader.fragment_shader, &shader.fragment_shader_length);
  glad_glCompileShader(fs_shader_obj);
  glad_glAttachShader(shader_program, fs_shader_obj);

  glad_glLinkProgram(shader_program);
  return shader_program;
}

void nv_gl_set_clear_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
  glad_glClearColor(r,g,b,a);
}

void nv_gl_render_clear() {
  glad_glClear(GL_COLOR_BUFFER_BIT);
}

void nv_gl_init() {
  gladLoadGL();
}

void init_quad(GLuint * quad_vbo, GLuint * quad_ibo) {
  float vec[] = {
    -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f, 0.0f, 1.0f
  };

  unsigned int ind[] = {
    0,1,2,
    0,2,3,
    4,5,6,
    4,6,7,
  };

  glad_glGenBuffers(1, quad_vbo);
  glad_glBindBuffer(GL_ARRAY_BUFFER, *quad_vbo);
  glad_glBufferData(GL_ARRAY_BUFFER, 2*sizeof(vec), vec, GL_STATIC_DRAW);

  glad_glGenBuffers(1, quad_ibo);
  glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *quad_ibo);
  glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);
}

void draw_quad(GLuint shader, GLuint vbo, GLuint ibo) {
  glad_glUseProgram(shader);
  glad_glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  
  // pos
  glad_glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
  glad_glEnableVertexAttribArray(0);

  glad_glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
  glad_glDisableVertexAttribArray(0);
  glad_glUseProgram(0);
}
