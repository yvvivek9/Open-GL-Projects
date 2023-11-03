#include<glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#define MAX 100000

double array[MAX][2];

//Function: Display Call back - used to draw the required visualization
//return type: void
//parameters: void
void display()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	/*glBegin(GL_POLYGON);
		glVertex2f(-0.2, -0.2);
		glVertex2f(0, 1);
		glVertex2f(1, -1);
	glEnd();*/
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Sets camera position with 3 input parameters: camera position, look at position and camera orientation
	gluLookAt(0, 1, 0, 0, 0, 0, 0, 0, 1);
	
	glBegin(GL_POLYGON);
		glColor3f(1, 0, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 1, 0);
			glVertex3f(0, 0, 1);
			glVertex3f(0, 1, 1);
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(1, 0, 0);
			glVertex3f(1, 0, 0);
			glVertex3f(1, 1, 0);
			glVertex3f(1, 0, 1);
			glVertex3f(1, 1, 1);
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(0, 1, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 1, 0);
			glVertex3f(1, 1, 0);
			glVertex3f(1, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(0, 1, 0);
			glVertex3f(0, 0, 1);
			glVertex3f(0, 1, 1);
			glVertex3f(1, 1, 1);
			glVertex3f(1, 0, 1);
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(0, 0, 1);
			glVertex3f(0, 0, 0);
			glVertex3f(1, 0, 0);
			glVertex3f(0, 0, 1);
			glVertex3f(1, 0, 1);
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(0, 0, 1);
			glVertex3f(0, 1, 0);
			glVertex3f(1, 1, 0);
			glVertex3f(0, 1, 1);
			glVertex3f(1, 1, 1);
	glEnd();


	//glutWireTeapot(0.5);

	glFlush();
}

int main(int argc, char* argv[])
{
	//Initialize glut
	glutInit(&argc, argv);

	//configure opengl window
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);


	//glutInitDisplayMode(GLUT_RGB); //for 2-D
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH); // for 3-D

	//create the Opengl window with a specific name
	glutCreateWindow("My First OpenGL Window");

	//for projection plane
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, 10, -10); 
	//gluPerspective(90, 1, 0.001, 1000);

	//register the callback for displaying
	glutDisplayFunc(display);

	//star the opengl loop 
	glutMainLoop();
}