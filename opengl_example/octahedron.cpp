#include "common_opengl.h"

GLfloat angle = 0.0f;

void display_octa(void) {
  static int list = 0;
  if (list == 0) {
    // Define octahedron vertices
    GLfloat PointA[] = {1, 0, 0}, PointB[] = {-1, 0, 0}, PointC[] = {0, 1, 0},
            PointD[] = {0, -1, 0}, PointE[] = {0, 0, 1}, PointF[] = {0, 0, -1};

    GLfloat ColorR[] = {1, 0, 0}, ColorG[] = {0, 1, 0}, ColorB[] = {0, 0, 1},
            ColorY[] = {1, 1, 0}, ColorCyan[] = {0, 1, 1}, ColorM[] = {1, 0, 1};

    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    glBegin(GL_TRIANGLES);

    // Top half
    ColoredVertex(ColorR, PointC);
    ColoredVertex(ColorG, PointA);
    ColoredVertex(ColorB, PointE);

    ColoredVertex(ColorY, PointC);
    ColoredVertex(ColorB, PointE);
    ColoredVertex(ColorCyan, PointB);

    ColoredVertex(ColorM, PointC);
    ColoredVertex(ColorCyan, PointB);
    ColoredVertex(ColorG, PointF);

    ColoredVertex(ColorR, PointC);
    ColoredVertex(ColorG, PointF);
    ColoredVertex(ColorG, PointA);

    // Bottom half
    ColoredVertex(ColorR, PointD);
    ColoredVertex(ColorB, PointE);
    ColoredVertex(ColorG, PointA);

    ColoredVertex(ColorY, PointD);
    ColoredVertex(ColorCyan, PointB);
    ColoredVertex(ColorB, PointE);

    ColoredVertex(ColorM, PointD);
    ColoredVertex(ColorG, PointF);
    ColoredVertex(ColorCyan, PointB);

    ColoredVertex(ColorR, PointD);
    ColoredVertex(ColorG, PointA);
    ColoredVertex(ColorG, PointF);

    glEnd();
    glEndList();
    glEnable(GL_DEPTH_TEST);
  }
  // A display list has been created, which will be called each time a regular
  // tetrahedron is drawn
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glRotatef(angle, 1, 0.5, 0);
  glCallList(list);
  glPopMatrix();
  glutSwapBuffers();
}

void idle_octahedron(void) {
  ++angle;
  if (angle >= 360.0f) {
    angle = 0.0f;
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  display_octa();
}

void rotate_octa(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowPosition(200, 200);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("OpenGL Window");
  glutDisplayFunc(&display_octa);

  glutIdleFunc(&idle_octahedron);
  glutMainLoop();
}

int main(int argc, char *argv[]) {
  std::cout << "Starting program\n";

  rotate_octa(argc, argv);

  std::cout << "...program completed\n";
  return 0;
}
