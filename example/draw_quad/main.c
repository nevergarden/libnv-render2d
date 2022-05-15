#include <nv_render2d_types.h>
#include <nv_transform2d.h>
#include <nv_render2d.h>
#include <GL/freeglut.h>
#include <GL/freeglut_std.h>

GLuint generic_shader;
GLuint generic_quad_vbo;
GLuint generic_quad_ibo;

static void display() {
  nv_gl_render_clear();
  nv_mesh2d_t mesh[2] = {
    {
      {0.2, -0.5},
      {0.2, 0.2},
      0
    },
    {
      {0.2, 0.5},
      {0.2, 0.2},
      0
    }
  };
  nv_transform2d(mesh, 2, &generic_quad_vbo);
  draw_quad(generic_shader, generic_quad_vbo, generic_quad_ibo);
  glutSwapBuffers();
}

static void idle() {
  glutPostRedisplay();
}

int main(int argc, char * argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Draw Quad");
  glutDisplayFunc(display);
  glutIdleFunc(idle);

  // init nv
  nv_gl_init();
  nv_gl_set_clear_color(0, 0, 0, 1);
  generic_shader = nv_gl_compile_generic_shader();
  init_quad(&generic_quad_vbo, &generic_quad_ibo);

  glutMainLoop();
  return 0;
}
