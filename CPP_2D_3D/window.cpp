#include "window.h"

double angle = 0.0;
void timer( int value )
{
    
    angle += 0.1;
    glutTimerFunc( 16, timer, 0 );
    glutPostRedisplay();
}

void Window::generate_spheres(int numSpheres)
{
    m_Spheres.reserve(numSpheres);
    initialize_spheres(m_Spheres, numSpheres, is3D);
}

void Window::draw_spheres2D()
{
    long unsigned int i = 0;
    
    for (i = 0; i < m_Spheres.size(); i++) {
        glColor3f(m_Spheres[i].m_color.r, m_Spheres[i].m_color.g, m_Spheres[i].m_color.b);
        glTranslatef(m_Spheres[i].m_position.x, m_Spheres[i].m_position.y, 0);
        gluDisk(gluNewQuadric(), 0.0, m_Spheres[i].m_radius, 20, 10);
        glTranslatef(-m_Spheres[i].m_position.x, -m_Spheres[i].m_position.y, 0);
    }
}

void Window::draw_spheres3D()
{
    long unsigned int i = 0;
    
    for (i = 0; i < m_Spheres.size(); i++) {
        glColor3f(m_Spheres[i].m_color.r, m_Spheres[i].m_color.g, m_Spheres[i].m_color.b);
        glTranslatef(m_Spheres[i].m_position.x, m_Spheres[i].m_position.y, m_Spheres[i].m_position.z);
        //gluSphere(gluNewQuadric(), m_Spheres[i].m_radius, 20, 10);
        glutSolidSphere(m_Spheres[i].m_radius, 20, 10);
        glTranslatef(-m_Spheres[i].m_position.x, -m_Spheres[i].m_position.y, m_Spheres[i].m_position.z);
    }
}

void Window::update_positions()
{
    long unsigned int i;

    for (i=0; i < m_Spheres.size(); i++) {
        brownian_sim(m_Spheres[i].m_position, dt, is3D);
    }


    m_path.push_back(m_Spheres[0].m_position);
}

void Window::draw_path()
{
    long unsigned int i;

    glBegin(GL_LINE_STRIP);
    glColor3f(0.0,1.0,0.0);
    for (i=0; i < m_path.size(); i++){
        glVertex3f(m_path[i].x, m_path[i].y, m_path[i].z);
    }
    glEnd();
}

void Window::set_deltaT(double new_dt)
{
    this->dt = new_dt;
}

Window::Window(bool s_3D)
{
    is3D = s_3D;

    if (s_3D){
       glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  
        glutInitWindowSize(800,600);
        glutInitWindowPosition(50,50);
        glutCreateWindow("Brownian 3D");
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
    }

    else{

        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Display mode takes parameters (Using parameters defined as
                                                // masks, hence the bitwise or | ) that specificy the mode
                                                // Here, it's using RBG and DOUBLE (buffering) defined in GLUT
        glutInitWindowSize(800,600);
        glutInitWindowPosition(50,50);
        glutCreateWindow("Brownian Motion");                    // 
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glMatrixMode(GL_PROJECTION);                  // Specifying that we will use projection matrix [x,y,z,w]
        glLoadIdentity();                             //
        gluOrtho2D(-LENGTH, LENGTH, -HEIGHT, HEIGHT); // Puts in the projection matrix an orthogonal projection of 
                                                // specified parameters
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();  
        glDisable(GL_LIGHTING);                       // Disable because 2D
        glEnable(GL_LINE_SMOOTH);                     // Basically anti-aliasing?
        glLineWidth(0.1);     

    }
}

void Window::reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

void Window::display()
{
    glClear(GL_COLOR_BUFFER_BIT); //
    glPushMatrix();  
    //glRotatef(theta,0,0,1); 

    
    this->draw_spheres2D();
    // Update sphere position
    this->update_positions();
    // Draw path
    this->draw_path();


    glFlush();                    // Flush buffer handeled by GL
    glutSwapBuffers();            // Swap with buffer displayed (remember the double buffering)
    glPopMatrix();  
    //theta+=dtheta; 
}

void Window::draw_axes()
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
void Window::display3D()
{


    glClear(GL_COLOR_BUFFER_BIT); //
    glPushMatrix();  
    //glRotatef(theta,0,0,1); 

    // Rotate Camera
    glRotated(angle, 0, 0, 1);

    this->draw_axes();
    this->draw_spheres3D();


    glFlush();                    // Flush buffer handeled by GL
    glutSwapBuffers();            // Swap with buffer displayed (remember the double buffering)
    glPopMatrix();  
    //theta+=dtheta; 
}

Window::~Window()
{
    exit(1);
}
