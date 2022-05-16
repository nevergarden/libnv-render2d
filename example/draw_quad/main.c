#include <nv_render2d_shader.h>
#include <nv_render2d_types.h>
#include <nv_transform2d.h>
#include <nv_render2d.h>
#include <GL/freeglut.h>
#include <GL/freeglut_std.h>

nv_gl_f_vertex_buffer_t buffer;

static void display() {
  nv_gl_render_clear();
  nv_gl_draw_triangle_from_f_vertex_array(&buffer);
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

  nv_mesh2d_t mesh[2] = {
    {
      {0.2, -0.5},
      {0.2, 0.2},
      0,
      NULL
    },
    {
      {0.2, 0.5},
      {0.2, 0.2},
      0,
      NULL
    }
  };
  mesh[0].triangles = malloc(sizeof(float)*12);
  mesh[1].triangles = malloc(sizeof(float)*12);
  nv_transform2d(mesh, 2);
  nv_gl_render2d_program_t program;
  nv_gl_create_shader_program(&program, nv_generic_quad_shader_vs, nv_generic_quad_shader_fs);
  nv_gl_create_f_vertex_array(&buffer, &program, DYNAMIC, 2);
  nv_gl_set_triangle_f_vertex_array(&buffer, 0, mesh[0].triangles);
  nv_gl_set_triangle_f_vertex_array(&buffer, 1, mesh[1].triangles);
  free(mesh[0].triangles);
  free(mesh[1].triangles);
  glutMainLoop();
  return 0;
}
