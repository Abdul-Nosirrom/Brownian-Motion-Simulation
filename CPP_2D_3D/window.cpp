#include "window.h"
//#include "base.h"

double angle = 0.0;
void timer( int value )
{
    
    angle += 0.1;
    glutTimerFunc( 16, timer, 0 );
    glutPostRedisplay();
}

void Window::generate_spheres(long unsigned int numSpheres)
{
    m_Spheres.reserve(numSpheres);
    initialize_spheres(m_Spheres, numSpheres, is3D);
    //set_temperature();
}

void Window::draw_spheres2D()
{
    long unsigned int i = 0;
    long unsigned int drawSize = showParticles ? m_Spheres.size() : 1;
    for (i = 0; i < drawSize; i++) {
        glColor3f(m_Spheres[i]->m_color.r, m_Spheres[i]->m_color.g, m_Spheres[i]->m_color.b);
        glTranslatef(m_Spheres[i]->m_position.x, m_Spheres[i]->m_position.y, 0);
        glutSolidSphere(m_Spheres[i]->m_radius, 200, 10);
        glTranslatef(-m_Spheres[i]->m_position.x, -m_Spheres[i]->m_position.y, 0);
    }
}

void Window::draw_spheres3D()
{
    long unsigned int i = 0;
    long unsigned int drawSize = showParticles ? m_Spheres.size() : 1;
    for (i = 0; i < drawSize; i++) {
        glPushMatrix();
        glColor3f(m_Spheres[i]->m_color.r, m_Spheres[i]->m_color.g, m_Spheres[i]->m_color.b);
        glTranslatef(m_Spheres[i]->m_position.x, m_Spheres[i]->m_position.y, m_Spheres[i]->m_position.z);
        glutSolidSphere(m_Spheres[i]->m_radius, 200, 10);
        glPopMatrix();
    }
}

void Window::update_positions()
{
    static double time = 0;
    long unsigned int i;

    for (i=0; i < m_Spheres.size(); i++) {
        m_Spheres[i]->border_collision();
        //intersphere_collision(m_Spheres);
        //brownian_sim(m_Spheres[i].m_position, dt, is3D);
        handleSphereSphereCollisions(m_Spheres);
        m_Spheres[i]->m_position.x += m_Spheres[i]->m_velocity.x*dt;
        m_Spheres[i]->m_position.y += m_Spheres[i]->m_velocity.y*dt;
        m_Spheres[i]->m_position.z += m_Spheres[i]->m_velocity.z*dt;
    }
    if (m_Spheres.size() == 1)
        brownian_sim(m_Spheres[0]->m_position, dt, is3D);
    time += dt;

    fprintf(outputData, "%lf %lf %lf\n", time, m_Spheres[0]->m_position.x, m_Spheres[0]->m_position.y);

    m_path.push_back(m_Spheres[0]->m_position);
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

void Window::set_temperature()
{
    GLfloat T, vel;
    std::cout << "Enter Temperature: ";
    std::cin >> T;
    long unsigned int iter;
    for (iter=0; iter < m_Spheres.size(); iter++)
    {
        vel = boltz(T);
        m_Spheres[iter]->m_velocity = (m_Spheres[iter]->m_velocity.normalized())*vel;
        std::cout << m_Spheres[iter]->m_velocity.x <<" "<< m_Spheres[iter]->m_velocity.y <<" "<< m_Spheres[iter]->m_velocity.z << std::endl;
    }

    
}


Window::Window(bool s_3D)
{
    is3D = s_3D;
    outputData = fopen("data", "a");

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
        gluLookAt(40,40,40,0,0,0,0,0,1); // Change screen size
        //glEnable(GL_LIGHTING);
        //glEnable(GL_NORMALIZE);
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
        //glEnable(GL_LIGHTING);                       // Disable because 2D
        glDisable(GL_LIGHTING);
        //glEnable(GL_NORMALIZE);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //
    glPushMatrix();  
    //glRotatef(theta,0,0,1); 

    
    this->draw_spheres2D();
    // Update sphere position
    this->update_positions();
    // Draw path
    this->draw_path();


    //glFlush();                    // Flush buffer handeled by GL
    glutSwapBuffers();            // Swap with buffer displayed (remember the double buffering)
    glPopMatrix();  
    //theta+=dtheta; 
}

void Window::draw_axes()
{
    glBegin(GL_LINE_STRIP);
        glColor3f(0,0,0);
        glVertex3f(-LENGTH,-HEIGHT,DEPTH);
        glVertex3f(LENGTH,-HEIGHT,DEPTH);
        glVertex3f(LENGTH,-HEIGHT,-DEPTH);
        glVertex3f(-LENGTH,-HEIGHT,-DEPTH);
        glVertex3f(-LENGTH,-HEIGHT,DEPTH);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(0,0,0);
        glVertex3f(-LENGTH,HEIGHT,DEPTH);
        glVertex3f(LENGTH,HEIGHT,DEPTH);
        glVertex3f(LENGTH,HEIGHT,-DEPTH);
        glVertex3f(-LENGTH,HEIGHT,-DEPTH);
        glVertex3f(-LENGTH,HEIGHT,DEPTH);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(0,0,0);
        glVertex3f(-LENGTH,HEIGHT,DEPTH);
        glVertex3f(-LENGTH,-HEIGHT,DEPTH);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(0,0,0);
        glVertex3f(-LENGTH,HEIGHT,-DEPTH);
        glVertex3f(-LENGTH,-HEIGHT,-DEPTH);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(0,0,0);
        glVertex3f(LENGTH,HEIGHT,DEPTH);
        glVertex3f(LENGTH,-HEIGHT,DEPTH);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(0,0,0);
        glVertex3f(LENGTH,HEIGHT,-DEPTH);
        glVertex3f(LENGTH,-HEIGHT,-DEPTH);
    glEnd();
}

/* Does the job */
void Window::display3D()
{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //
    glPushMatrix();  
    //glRotatef(theta,0,0,1); 

    // Rotate Camera
    glRotated(angle, 0, 0, 1);
    //glPopMatrix();
    glPushMatrix();
    this->draw_path();
    glPopMatrix();      // PLACED DRAW PATH BEFORE SPHERE SO SPHERE OVERLAPS IT (EDIT)
    //glPopMatrix();
    this->draw_spheres3D();
        // Update sphere position
    this->update_positions();
    // Draw path
    //glPopMatrix();
    
    //glPushMatrix();
    this->draw_axes();

    //glFlush();                    // Flush buffer handeled by GL
    glutSwapBuffers();            // Swap with buffer displayed (remember the double buffering)
    glPopMatrix();  
    //theta+=dtheta; 
}

Window::~Window()
{
    fclose(outputData);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush(); 
    glutSwapBuffers();
    exit(0);
}
