// A simple introductory program; its main window contains a static picture
// of a series of points

#include <GL/glut.h>

// Clears the current window and draws a bunch of points.
void display() {
  glPointSize(10);
  glBegin(GL_POINTS);
  for (unsigned int i = 0; i < 10; i++) {
    glColor3f(0, 0.1 * i, 0);
    glVertex3d(0, 0.1 * i, 0);
  }
  glEnd();

  // Flush drawing command buffer to make drawing happen as soon as possible.
  glFlush();
}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// enters the main event loop.
int main(int argc, char** argv) {
  // Use a single buffered window in RGB mode (as opposed to a double-buffered
  // window or color-index mode).
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  // Position window at (80,80)-(480,380) and give it a title.
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(400, 300);
  glutCreateWindow("A Simple Triangle");

  // Tell GLUT that whenever the main window needs to be repainted that it
  // should call the function display().
  glutDisplayFunc(display);

  // Tell GLUT to start reading and processing events.  This function
  // never returns; the program only exits when the user closes the main
  // window or kills the process.
  glutMainLoop();
}