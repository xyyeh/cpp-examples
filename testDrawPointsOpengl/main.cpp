
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>

// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f;

void drawObject() {
  glPointSize(5);
  glBegin(GL_POINTS);
  for (unsigned int i = 0; i < 30; i++) {
    float x = (rand() % 100 - 50) / 100.0;
    float y = (rand() % 100 - 50) / 100.0;
    float z = (rand() % 100 - 50) / 100.0;
    glColor3f(x, y, z);
    glVertex3f(x, y, z);
  }
  glEnd();
}

void renderScene(void) {
  // Clear Color and Depth Buffers

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Reset transformations
  glLoadIdentity();
  // Set the camera
  gluLookAt(x, 1.0f, z, x + lx, 1.0f, z + lz, 0.0f, 1.0f, 0.0f);

  // Draw ground
  glColor4f(0.9f, 0.9f, 0.9f, 0.1f);
  glBegin(GL_QUADS);
  glVertex3f(-100.0f, 0.0f, -100.0f);
  glVertex3f(-100.0f, 0.0f, 100.0f);
  glVertex3f(100.0f, 0.0f, 100.0f);
  glVertex3f(100.0f, 0.0f, -100.0f);
  glEnd();

  // Draw object
  drawObject();

  glutSwapBuffers();
}

void changeSize(int w, int h) {
  // Prevent a divide by zero, when window is too short
  // (you cant make a window of zero width).
  if (h == 0) h = 1;
  float ratio = w * 1.0 / h;

  // Use the Projection Matrix
  glMatrixMode(GL_PROJECTION);

  // Reset Matrix
  glLoadIdentity();

  // Set the viewport to be the entire window
  glViewport(0, 0, w, h);

  // Set the correct perspective.
  gluPerspective(45.0f, ratio, 0.1f, 100.0f);

  // Get Back to the Modelview
  glMatrixMode(GL_MODELVIEW);
}

void processNormalKeys(unsigned char key, int x, int y) {
  if (key == 27) exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {
  float fraction = 0.5f;

  switch (key) {
    case GLUT_KEY_LEFT:
      angle -= 0.05f;
      lx = sin(angle);
      lz = -cos(angle);
      break;
    case GLUT_KEY_RIGHT:
      angle += 0.05f;
      lx = sin(angle);
      lz = -cos(angle);
      break;
    case GLUT_KEY_UP:
      x += lx * fraction;
      z += lz * fraction;
      break;
    case GLUT_KEY_DOWN:
      x -= lx * fraction;
      z -= lz * fraction;
      break;
  }
}

int main(int argc, char **argv) {
  // init GLUT and create window

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(320, 320);
  glutCreateWindow("GLUT Tutorial");

  // register callbacks
  glutDisplayFunc(renderScene);
  glutReshapeFunc(changeSize);
  glutIdleFunc(renderScene);
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(processSpecialKeys);

  // OpenGL init
  glEnable(GL_DEPTH_TEST);

  // enter GLUT event processing cycle
  glutMainLoop();

  return 1;
}