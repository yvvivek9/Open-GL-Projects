
#include <GL/glut.h>
#include <GL/GL.h>
#include <iostream>
#include <cmath>

double pi = 2 * acos(0.0);

// constants for camera
double xrot = 0.0f;
double yrot = 0.0f;
double xdiff = 0.0f;
double ydiff = 0.0f;
bool mouseDown = false;
double valZoom = 20.0;
double camX = 20.0, camY = 20.0, camZ = 20.0;

// constants for angles
double neckAngle = 0;
double headAngle = 0;
double leftLeg = 0;
double leftAnkle = 0;
double rightLeg = 0;
double rightAnkle = 0;

double xmov = 0;
double ymov = 0;

enum action {leftMove, rightMove, initial, none};
action movement = none;

enum fly {halt, goingUp, comingDown};
fly flyingStatus = halt;
double wingAngle = 30;
double wingSin = 0;


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

    //glBegin(GL_LINES); // X - axis
    //glColor3f(1, 0, 0);
    //glVertex3f(-20, 0, 0);
    //glVertex3f(20, 0, 0);
    //glEnd();

    //glBegin(GL_LINES); // Y - axis
    //glColor3f(0, 1, 0);
    //glVertex3f(0, -20, 0);
    //glVertex3f(0, 20, 0);
    //glEnd();

    //glBegin(GL_LINES); // Z - axis
    //glColor3f(0, 0, 1);
    //glVertex3f(0, 0, 20);
    //glVertex3f(0, 0, -20);
    //glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 1, 0);
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 150);
    glVertex3f(40, -12.8, 40);
    glVertex3f(40, -12.8, -40);
    glVertex3f(-40, -12.8, -40);
    glVertex3f(-40, -12.8, 40);
    glEnd();

    

    // base matrix
    glTranslatef(xmov, ymov, 0);
    glPushMatrix();

    // body
    glPushMatrix();
        glColor3f(0.54, 0.21, 0.04);
        setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 100);
        glScalef(3, 1, 1);
        glutSolidCube(5.0);
    glPopMatrix();

    //left wing
    glPushMatrix();
    glTranslatef(0, 1, 1.5);
    glRotatef(wingAngle * sin(wingSin), 1, 0, 0);
    glColor3f(1, 1, 1);
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 100);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(4, 0, 7);
    glVertex3f(-4, 0, 7);
    glEnd();
    glPopMatrix();

    //right wing
    glPushMatrix();
    glTranslatef(0, 1, -1.5);
    glRotatef(-wingAngle * sin(wingSin), 1, 0, 0);
    glColor3f(1, 1, 1);
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 100);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(4, 0, -7);
    glVertex3f(-4, 0, -7);
    glEnd();
    glPopMatrix();

    

    // neck - part
    glPushMatrix();
        
        // neck - neck
        glTranslatef(7.0, 3.0, 0);
        glRotatef(neckAngle, 0, 0, 1);
        glTranslatef(0.75, 2.0, 0);
        glPushMatrix();
            glColor3f(0.54, 0.21, 0.04);
            setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
            glRotatef(70, 0, 0, 1);
            glScalef(3, 1, 1);
            glutSolidCube(2);
        glPopMatrix();

        // neck - head
        glTranslatef(1.7, 2.2, 0);
        glPushMatrix();
            glColor3f(0.54, 0.21, 0.04);
            setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
            glRotatef(-20 + headAngle, 0, 0, 1);
            glScalef(1.5, 1, 1);
            glutSolidCube(2.5);
        glPopMatrix();

    glPopMatrix();

    // tail 
    /*glPushMatrix();
    glColor3f(0.23, 0.1, 0.03);
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(-11, -1, 0);
    glRotatef(40, 0, 0, 1);
    glScalef(5, 1, 1);
    glutSolidSphere(1, 20, 20);
    glPopMatrix();*/

    //suhrid tail
    glPushMatrix();
    glColor3f(0.23, 0.1, 0.03);
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(-10, -1, 0);
    glRotatef(40, 0, 0, 1);
    glScalef(5, 1, 1);
    glutSolidSphere(0.75, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.23, 0.1, 0.03);
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(-11.55, -1.5, 0);
    glRotatef(40, 0, 0, 1);
    glScalef(5, 1, 1);
    glutSolidSphere(0.8, 20, 5);
    glPopMatrix();


    // front left leg
    glPushMatrix();
    glColor3f(0.72, 0.31, 0.09);
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    
        glTranslatef(6, 0, -1.5);
        glRotatef(leftLeg, 0, 0, 1);
        glPushMatrix();
        glTranslatef(0, -3, 0);
        glScalef(1, 5, 1);
        glutSolidSphere(1, 20, 20);
        glPopMatrix();

        glTranslatef(0, -6, 0);
        glRotatef(leftAnkle, 0, 0, 1);
        glPushMatrix();
        glTranslatef(0, -3, 0);
        glScalef(1, 4, 1);
        glutSolidSphere(1, 20, 20);
        glPopMatrix();

    glPopMatrix();

    //front right leg
    glPushMatrix();
    glColor3f(0.72, 0.31, 0.09);
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);

        glTranslatef(6, 0, 1.5);
        glRotatef(rightLeg, 0, 0, 1);
        glPushMatrix();
        glTranslatef(0, -3, 0);
        glScalef(1, 5, 1);
        glutSolidSphere(1, 20, 20);
        glPopMatrix();

        glTranslatef(0, -6, 0);
        glRotatef(rightAnkle, 0, 0, 1);
        glPushMatrix();
        glTranslatef(0, -3, 0);
        glScalef(1, 4, 1);
        glutSolidSphere(1, 20, 20);
        glPopMatrix();

    glPopMatrix();

    //rear left leg
    glPushMatrix();
    glColor3f(0.72, 0.31, 0.09);
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);

        glTranslatef(-6, 0, -1.5);
        glRotatef(leftLeg, 0, 0, 1);
        glPushMatrix();
        glTranslatef(0, -3, 0);
        glScalef(1, 5, 1);
        glutSolidSphere(1, 20, 20);
        glPopMatrix();

        glTranslatef(0, -6, 0);
        glRotatef(leftAnkle, 0, 0, 1);
        glPushMatrix();
        glTranslatef(0, -3, 0);
        glScalef(1, 4, 1);
        glutSolidSphere(1, 20, 20);
        glPopMatrix();

    glPopMatrix();

    //rear right leg
    glPushMatrix();
    glColor3f(0.72, 0.31, 0.09);
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);

        glTranslatef(-6, 0, 1.5);
        glRotatef(rightLeg, 0, 0, 1);
        glPushMatrix();
        glTranslatef(0, -3, 0);
        glScalef(1, 5, 1);
        glutSolidSphere(1, 20, 20);
        glPopMatrix();

        glTranslatef(0, -6, 0);
        glRotatef(rightAnkle, 0, 0, 1);
        glPushMatrix();
        glTranslatef(0, -3, 0);
        glScalef(1, 4, 1);
        glutSolidSphere(1, 20, 20);
        glPopMatrix();

    glPopMatrix();

    // base matrix end
    glPopMatrix();


    /* flush drawing routines to the window */
    glFlush();

}

void animate()
{
    if (movement == initial) {
        xmov += 0.0005;
        if (leftLeg < 30) {
            leftLeg += 0.01;
            leftAnkle -= 0.01;
        }
        else {
            movement = rightMove;
        }
    }
    if (movement == rightMove) {
        xmov += 0.0005;
        if (rightLeg < 30) {
            rightLeg += 0.01;
            rightAnkle -= 0.01;
            leftLeg -= 0.01;
            leftAnkle += 0.01;
        }
        else {
            movement = leftMove;
        }
    }
    if (movement == leftMove) {
        xmov += 0.0005;
        if (rightLeg > 0) {
            rightLeg -= 0.01;
            rightAnkle += 0.01;
            leftLeg += 0.01;
            leftAnkle -= 0.01;
        }
        else {
            movement = rightMove;
        }
    }

    if (flyingStatus != halt) {
        wingSin += 0.002;
    }

    if (flyingStatus == goingUp) {
        if (ymov < 10) {
            ymov += 0.001;
        }
    }
    if (flyingStatus == comingDown) {
        if (ymov > 0) {
            ymov -= 0.001;
        }
        else {
            flyingStatus = halt;
        }
    }

    glutPostRedisplay();
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
    switch (key) {
        case 'd':
        case 'D': if (movement == none) movement = initial; break;
        case 'a':
        case 'A': movement = none; break;
        case 'w':
        case 'W': flyingStatus = goingUp; break;
        case 's':
        case 'S': flyingStatus = comingDown; break;
        default: break;
    }
}

void arrowKey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        valZoom = valZoom - 0.5; break;
    case GLUT_KEY_DOWN:
        valZoom = valZoom + 0.5; break;
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
    //gluLookAt(camerax, cameray, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

    glutMouseFunc(sphereMouseEvent);
    glutMotionFunc(sphereMouseMotion);
    glutKeyboardFunc(keyBoard);
    glutSpecialFunc(arrowKey);

    //register the IdleFunction
    glutIdleFunc(animate);

    /* tell GLUT to wait for events */
    glutMainLoop();
}


