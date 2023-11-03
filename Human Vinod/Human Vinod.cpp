#define  GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <GL/GL.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#define MAX 100000
#define PI 3.14159265358979323846

float angle = 0;
float angle2 = 90;
float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;
bool mouseDown = false;

float tX = 0;
float tY = 0;
float tZ = 0;

double valZoom = 1;

double camX = 0, camY = 0, camZ = 1.0;

void animate()
{

    angle = angle + 0.5;
    angle2 = angle2 - 0.5;
    if (angle > 180)
    {
        angle = 0;
    }



    glutPostRedisplay();
}

double array[MAX][2];

//Function: Display Call back - used to draw the required visualization
//return type: void
//parameters: void

void initLight()
{
    /* set up lights */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //GLfloat lightpos[] = { 0.0, 0.0, 15.0 };
    GLfloat lightcolor[] = { 0.5, 0.5, 0.5 };
    GLfloat ambcolor[] = { 0.2, 0.2, 0.2 };
    GLfloat specular[] = { 1.0, 1.0, 1.0 };

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    //glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambcolor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcolor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    glEnable(GL_COLOR_MATERIAL); // tells opengl to maintain the original color of the object
}
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



void atom()
{
    glBegin(GL_RENDER);
    glColor3f(0.878, 1, 1);
    glScalef(1, 3, 1);
    glutSolidSphere(0.025, 100, 100);
    glEnd();

}

void face()
{
    glBegin(GL_LOAD);
    glColor3f(1, 1, 1);
    glScalef(1, 1.5, 1);
    glutSolidSphere(0.05, 100, 100);
    glEnd();
}

void neck()
{
    glBegin(GL_LOAD);
    glColor3f(0.878, 1, 1);
    glScalef(1, 2, 1);
    glutSolidSphere(0.015, 100, 100);
    glEnd();

}

void ball()
{
    glBegin(GL_LOAD);
    glScalef(1, 1, 1);
    glutSolidSphere(0.025, 100, 100);
    glEnd();

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(0,0, 1, 0, 0, 0, 0, 1, 0);
    //gluLookAt(0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    gluLookAt(
        camX, camY, camZ,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    );
    glTranslatef(tX, tY, tZ);

    //body
    glPushMatrix();
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(0, 0, 0);
    atom();
    glPopMatrix();
    glPushMatrix();
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(0, 0.15, 0);
    atom();
    glPopMatrix();

    //hip
    glPushMatrix();
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef((0.075 * cos(0.523)), -(0.075 + (0.075 * sin(0.523))), 0);
    glRotatef(60, 0, 0, 1);
    atom();
    glPopMatrix();

    glPushMatrix();
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(-(0.075 * cos(0.523)), -(0.075 + (0.075 * sin(0.523))), 0);
    glRotatef(-60, 0, 0, 1);
    atom();
    glPopMatrix();

    //thigh
    glPushMatrix();
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef((0.15 * cos(0.523)), -(0.15 + (0.15 * sin(0.523))), 0);
    //glRotatef(0, 0, 0, 1);
    atom();
    glPopMatrix();

    glPushMatrix();
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(-(0.15 * cos(0.523)), -(0.15 + (0.15 * sin(0.523))), 0);
    //glRotatef(0, 0, 0, 1);
    atom();
    glPopMatrix();

    //leg
    glPushMatrix();
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef((0.15 * cos(0.523)), -(0.3 + (0.15 * sin(0.523))), 0);
    //glRotatef(0, 0, 0, 1);
    atom();
    glPopMatrix();
    glPushMatrix();
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef((-0.15 * cos(0.523)), -(0.3 + (0.15 * sin(0.523))), 0);
    //glRotatef(0, 0, 0, 1);
    atom();
    glPopMatrix();

    //shoulder
    glPushMatrix();
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(0.075, 0.225, 0);
    glRotatef(90, 0, 0, 1);
    atom();
    glPopMatrix();
    glPushMatrix();
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(-0.075, 0.225, 0);
    glRotatef(90, 0, 0, 1);
    atom();
    glPopMatrix();

    //hands
    glPushMatrix();//r1
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(0.15, 0.15, 0);//neutralization
    glTranslatef(0, 0.075, 0);
    //glRotatef(angle, 1, 0, 0);
    glTranslated(0, -0.075, 0);//translation
    atom();
    glPopMatrix();
    glPushMatrix();//l1
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(-0.15, 0.15, 0);
    //glRotatef(0, 0, 0, 1);
    glTranslatef(0, 0.075, 0);
    //glRotatef(-angle, 1,0,0);
    glTranslatef(0, -0.075, 0);

    atom();
    glPopMatrix();
    glPushMatrix();//r2
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(0.15, 0, 0);
    glTranslatef(0, 0.075, 0);
    if (angle > 0 && angle < 90)
        glRotatef(-angle, 1, 0, 0);
    if (angle >= 90 && angle < 180)
        glRotatef(angle + 180, 1, 0, 0);

    glTranslated(0, -0.075, 0);
    atom();
    glPopMatrix();




    glPushMatrix();//l2
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(-0.15, 0, 0);
    glTranslatef(0, 0.075, 0);
    if (angle > 0 && angle < 90)
        glRotatef(-angle, 1, 0, 0);
    if (angle >= 90 && angle < 180)
        glRotatef(angle + 180, 1, 0, 0);
    glTranslatef(0, -0.075, 0);
    atom();
    glPopMatrix();

    //neck
    glPushMatrix();
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(0, 0.255, 0);
    neck();
    glPopMatrix();

    //face
    glPushMatrix();
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(0, 0.36, 0);
    face();
    glPopMatrix();

    //foot
    glPushMatrix();
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef((0.15 * cos(0.523)), -(0.4 + 0.15 * sin(0.523)), 0);
    ball();
    glPopMatrix();

    glPushMatrix();
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(-(0.15 * cos(0.523)), -(0.4 + 0.15 * sin(0.523)), 0);
    ball();
    glPopMatrix();

    //pam
    glPushMatrix();//r
    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(0.15, -0.1, 0);
    glTranslatef(0, 0.175, 0);//neutralization
    if (angle > 0 && angle < 90)
        glRotatef(-angle, 1, 0, 0);
    if (angle >= 90 && angle < 180)
        glRotatef(angle + 180, 1, 0, 0);
    glTranslatef(0, -0.175, 0);//translation

    ball();
    glPopMatrix();
    glPushMatrix();//l

    setMaterial(0.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 50);
    glTranslatef(-0.15, -0.1, 0);
    glTranslatef(0, 0.175, 0);//neutralization
    if (angle > 0 && angle < 90)
        glRotatef(-angle, 1, 0, 0);
    if (angle >= 90 && angle < 180)
        glRotatef(angle + 180, 1, 0, 0);
    glTranslatef(0, -0.175, 0);//translation

    ball();
    glPopMatrix();





    glFlush();
}
void reshape(int width, int height) {

    /* define the viewport transformation */
    glViewport(0, 0, width, height);
}

void keyBoard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'A':
    case 'a': tX = tX - 0.01; break;

    case 'D':
    case 'd': tX = tX + 0.01; break;

    case 'W':
    case 'w': tY = tY + 0.01; break;

    case 'S':
    case 's': tY = tY - 0.01; break;
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
    camX = valZoom * (cos(xrot * PI / 180) * sin(yrot * PI / 180));
    camY = valZoom * (sin(xrot * PI / 180));
    camZ = valZoom * (cos(xrot * PI / 180) * cos(yrot * PI / 180));
    glutPostRedisplay();
}

void sphereMouseMotion(int x, int y)
{
    if (mouseDown)
    {
        yrot = -(x + xdiff);
        xrot = (y + ydiff);
        if (xrot > 89) xrot = 89.0f;
        if (xrot < -89) xrot = -89.0f;

        //printf("(xrot, ytor)=(%f, %f)\n", xrot, yrot);
        camX = valZoom * (cos(xrot * PI / 180) * sin(yrot * PI / 180));
        camY = valZoom * (sin(xrot * PI / 180));
        camZ = valZoom * (cos(xrot * PI / 180) * cos(yrot * PI / 180));
        // printf("%d\n", valZoom);
    }
    glutPostRedisplay();
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
int main(int argc, char* argv[])
{
    //Initialize glut
    glutInit(&argc, argv);

    //configure opengl window
    glutInitWindowSize(750, 750);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

    //create the Opengl window with a specific name
    glutCreateWindow("Humanoid");
    glutDisplayFunc(display);

    glEnable(GL_DEPTH_TEST);

    initLight();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-10, 10, -10, 10, 10, -10);
    //gluPerspective(80, 1, 0.001, 1000);
    gluPerspective(60, 1, 0.01, 100);


    //register the callback for displaying
   // glutDisplayFunc(display);
    glutIdleFunc(animate);

    //Register keyboard and mouse movements function
    glutMouseFunc(sphereMouseEvent);
    glutMotionFunc(sphereMouseMotion);
    glutKeyboardFunc(keyBoard); // void keyBoard(unsigned char key, int x, int y);
    glutSpecialFunc(arrowKey); // void arrowKey(int key, intx, int y)
    //star the opengl loop
    glutMainLoop();
}

