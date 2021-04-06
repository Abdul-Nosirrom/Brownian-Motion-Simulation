#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "spheres.h"

sphere *allSpheres;
LinkedList particleHistory;


double angle = 0.0;
void timer( int value )
{
    angle += 0.1;
    glutTimerFunc( 16, timer, 0 );
    glutPostRedisplay();
}

void draw_axes()
{
  glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex3f(-100,0,0);
    glVertex3f(100,0,0);
  glEnd();

  glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex3f(0,-100,0);
    glVertex3f(0,100,0);
  glEnd();

  glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex3f(0,0,-100);
    glVertex3f(0,0,100);
  glEnd();
}

/* Does the job */
void display(void)
{


    glClear(GL_COLOR_BUFFER_BIT); //
    glPushMatrix();  
    //glRotatef(theta,0,0,1); 

    // Rotate Camera
    glRotated(angle, 0, 0, 1);

    draw_axes();

    drawSphere(allSpheres);
    spherePos(allSpheres, 7, particleHistory);
    draw_path(&particleHistory);


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
    particleHistory = initialize_list();
    int numSpheres;
    printf("Input the number of particles:  ");
    scanf("%d", &numSpheres);

    allSpheres = initializeSphere(numSpheres);
  /* 
   * Using GL Utilities (glut) 
   *
   */

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  
    glutInitWindowSize(800,600);
    glutInitWindowPosition(50,50);
    glutCreateWindow(argv[0]);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double w = glutGet(GLUT_WINDOW_WIDTH);
    double h = glutGet(GLUT_WINDOW_HEIGHT);
    gluPerspective(75, w/h, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(100,100,100,0,0,0,0,0,1);
    
    glutTimerFunc(0,timer,0);
    glEnable(GL_LINE_SMOOTH);                     // Basically anti-aliasing?
    glLineWidth(3.0);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    glutMainLoop();
  /*
    glutInit(&argc, argv);                        // Initializes the GL Utilities
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Display mode takes parameters (Using parameters defined as
                                                // masks, hence the bitwise or | ) that specificy the mode
                                                // Here, it's using RBG and DOUBLE (buffering) defined in GLUT
    glutInitWindowSize(1000,500);
    glutInitWindowPosition(50,50);
    glutCreateWindow(argv[0]);                    // 
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);                  // Specifying that we will use projection matrix [x,y,z,w]
    glLoadIdentity();                             //
    //gluOrtho2D(-LENGTH, LENGTH, -HEIGHT, HEIGHT); // Puts in the projection matrix an orthogonal projection of 
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
*/
    free(allSpheres);
    destroy_list(&particleHistory);
    allSpheres = NULL;
    return 0;   
}