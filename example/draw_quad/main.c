#include <nv_render2d.h>
#include <GL/freeglut.h>
#include <GL/freeglut_std.h>

static void display() {
  // init_quad();
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
  glutMainLoop();
  return 0;
}
