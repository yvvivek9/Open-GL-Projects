#include <GL/glut.h>
#include <GL/GL.h>
#include <iostream>
#include <cmath>

float pi = 2 * acos(0.0);

float potAngle = 0;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;
bool mouseDown = false;

double valZoom = 10.0;

double camX = 0, camY = 0, camZ = 10.0;

float tX = 0; float tY = 0; float tZ = 0;


void setMaterial(GLfloat ambientR, GLfloat ambientG, GLfloat ambientB,
    GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB,
    GLfloat specularR, GLfloat specularG, GLfloat specularB,
    GLfloat shininess) {

    GLfloat ambient[] = { ambientR, ambientG, ambientB };
    GLfloat diffuse[] = { diffuseR, diffuseG, diffuseB };
    GLfloat specular[] = { specularR, specularG, specularB };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void display() {

    /* clear window */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* future matrix manipulations should affect the modelview matrix */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glBegin(GL_LINES); // X - axis
        glColor3f(1, 0, 0);
            glVertex3f(-10, 0, 0);
            glVertex3f(10, 0, 0);
    glEnd();

    glBegin(GL_LINES); // Y - axis
        glColor3f(0, 1, 0);
            glVertex3f(0, -10, 0);
            glVertex3f(0, 10, 0);
    glEnd();

    glBegin(GL_LINES); // Z - axis
        glColor3f(0, 0, 1);
            glVertex3f(0, 0, 10);
            glVertex3f(0, 0, -10);
    glEnd();

    //cylinder code
    /*float cylinder1Angle = 0;
    glPushMatrix();
    while (cylinder1Angle <= 2 * pi) {
        glBegin(GL_LINES);
        glColor3f(1, 1, 1);
        glVertex3f(-5, 2 * sin(cylinder1Angle), 2 * cos(cylinder1Angle));
        glVertex3f(5, 2 * sin(cylinder1Angle), 2 * cos(cylinder1Angle));
        glEnd();
        cylinder1Angle += 0.001;
    }
    glPopMatrix();*/


    glTranslatef(tX, tY, tZ);
    glPushMatrix(); 
    glColor3f(0.957, 0.643, 0.376);
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(3, 0, 0);
    glRotatef(potAngle, 1, 0, 0);
    glutSolidTeapot(1);
    glPopMatrix();


    glPushMatrix();
    glColor3f(0.85, 0.09, 0.18);
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(-3, 0, 0);
    glRotatef(-potAngle, 1, 0, 0);
    glutSolidTeapot(1);
    glPopMatrix();

    /* flush drawing routines to the window */
    glFlush();

}

void reshape(int width, int height) {

    /* define the viewport transformation */
    glViewport(0, 0, width, height);
}

void initLight()
{
    /* set up lights */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat lightpos[] = { 0.0, 0.0, 15.0 };
    GLfloat lightcolor[] = { 0.5, 0.5, 0.5 };
    GLfloat ambcolor[] = { 0.2, 0.2, 0.2 };
    GLfloat specular[] = { 1.0, 1.0, 1.0 };

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambcolor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcolor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    glEnable(GL_COLOR_MATERIAL); // tells opengl to maintain the original color of the object
}

void animate()
{
    potAngle += 0.1;
    //cameraAngle += 0.001;
    

    glutPostRedisplay();
}

/* Callback: The mouse click event is defined based on the number of view ports enabled
*/
void sphereMouseEvent(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseDown = true;
    }
    else
        mouseDown = false;

    if (mouseDown)
    {
        xdiff = (yrot + x);
        ydiff = -y + xrot;
    }

    if (mouseDown)
    {
        //mouseDown = true;
        xdiff = (yrot + x);
        ydiff = -y + xrot;
    }
}

/* Callback: Mouse movement on the sphere on left mouse down enables sphere rotation
*/
void sphereMouseMotion(int x, int y)
{
    if (mouseDown)
    {
        yrot = -(x + xdiff);
        xrot = (y + ydiff);
        if (xrot > 89) xrot = 89.0f;
        if (xrot < -89) xrot = -89.0f;

        //printf("(xrot, ytor)=(%f, %f)\n", xrot, yrot);
        camX = valZoom * (cos(xrot * pi / 180) * sin(yrot * pi / 180));
        camY = valZoom * (sin(xrot * pi / 180));
        camZ = valZoom * (cos(xrot * pi / 180) * cos(yrot * pi / 180));
        //printf("%f, %f, %f\n", camX, camY, camZ);
    }
    glutPostRedisplay();
}

void keyBoard(unsigned char key, int x, int y) {
    // X and Y holds the value of cursor location with respect to glut Window

    switch (key)
    {
        case 'A':
        case 'a': tX -= 0.1; break;

        case 'd':
        case 'D': tX += 0.1; break;

        case 'w':
        case 'W': tY += 0.1; break;

        case 's':
        case 'S': tY -= 0.1; break;

        case 'q':
        case 'Q': tZ += 0.1; break;

        case 'e':
        case 'E': tZ -= 0.1; break;
    
        default:
            break;
    }
    glutPostRedisplay();
}

void arrowKey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        valZoom = valZoom + 0.1; break;
    case GLUT_KEY_DOWN:
        valZoom = valZoom - 0.1; break;
    default:
        break;
    }
    camX = valZoom * (cos(xrot * pi / 180) * sin(yrot * pi / 180));
    camY = valZoom * (sin(xrot * pi / 180));
    camZ = valZoom * (cos(xrot * pi / 180) * cos(yrot * pi / 180));
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {

    /* initialize GLUT, using any commandline parameters passed to the
       program */
    glutInit(&argc, argv);

    /* setup the size, position, and display mode for new windows */
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

    /* create and set up a window */
    glutCreateWindow("my first openGL");
    glutDisplayFunc(display);

    /* set up depth-buffering */
    glEnable(GL_DEPTH_TEST);

    initLight();

    /* define the projection transformation */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 4, 100);

    /* define the viewing transformation */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(camerax, cameray, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

    glutMouseFunc(sphereMouseEvent);
    glutMotionFunc(sphereMouseMotion);
    glutKeyboardFunc(keyBoard); // void keyBoard(unsigned char key, int x, int y); 
    glutSpecialFunc(arrowKey); // void arrowKey(int key, intx, int y)

    //register the IdleFunction
    glutIdleFunc(animate);

    /* tell GLUT to wait for events */
    glutMainLoop();
}