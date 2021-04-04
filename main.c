#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define LENGTH 20.0
#define HEIGHT 10.0

void drawSphere(GLfloat x, GLfloat y, GLfloat z, GLboolean isLarge) 
{
    int radius;
    if (isLarge) {
        radius = 1.5;
        glColor3f(1.0,0.0,0.0);
    }
    else {
        radius = 0.5;
        glColor3f(1.0,1.0,1.0);
    }
    glTranslatef(x,y,z);
    gluDisk(gluNewQuadric(), 0.0, 2.0, 20, 10);
    glTranslatef(-x,-y,-z);
}

/* Does the job */
void display(void)
{
  //static float theta=20;
  //static float theta=0;
  //static float dtheta=0.1; 
  glClear(GL_COLOR_BUFFER_BIT); //
  glPushMatrix();  
  //glRotatef(theta,0,0,1); 

  drawSphere(2, 5 ,0, GL_TRUE);

  drawSphere(-3, -1, 0, GL_FALSE);

  glFlush();                    // Flush buffer handeled by GL
  glutSwapBuffers();            // Swap with buffer displayed (remember the double buffering)
  glPopMatrix();  
  //theta+=dtheta; 
}

/* Called from main() with size of a window (w,h) */
void reshape(int w, int h)
{
  glViewport(0, 0, w, h); // Modifies viewport/window size with projection matrix [x,y,z,w]
}

int main(int argc, char *argv[])
{
  /* 
   * Using GL Utilities (glut) 
   *
   */
  glutInit(&argc, argv);                        // Initializes the GL Utilities
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Display mode takes parameters (Using parameters defined as
                                                // masks, hence the bitwise or | ) that specificy the mode
                                                // Here, it's using RBG and DOUBLE (buffering) defined in GLUT
  glutInitWindowSize(1000,500);
  glutInitWindowPosition(50,50);
  glutCreateWindow(argv[0]);                    // 
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glMatrixMode(GL_PROJECTION);                  // Specifying that we will use projection matrix [x,y,z,w]
  glLoadIdentity();                             //
  gluOrtho2D(-LENGTH, LENGTH, -HEIGHT, HEIGHT); // Puts in the projection matrix an orthogonal projection of 
                                                // specified parameters
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();  
  glDisable(GL_LIGHTING);                       // Disable because 2D
  glEnable(GL_LINE_SMOOTH);                     // Basically anti-aliasing?
  glLineWidth(3.0);
  glutReshapeFunc(reshape);                     // Two below basically function overloading? but non-oop?
  glutDisplayFunc(display);
  glutIdleFunc(display);  
  glutMainLoop();                               // You know this from working with UI on the alarm clock
  return 0;   
}