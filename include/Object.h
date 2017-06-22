#ifndef Object_h_
#define Object_h_

/*****************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>

#include"MyGLUT.h"
#include"Colors.h"
#include"Define.h"

/* parameters for camera */
double dstnc = 100.0;
double theta = 200*PI/180;
double phi   = 50*PI/180;
double xc    = 0.0;
double yc    = 0.0;
double zc    = 0.0;

double speed = 0.0;

void glShaft(void);
void glRotor(void);

void glHandSpinner(void){
	static double r = 0.0;
	glShaft();

	glPushMatrix();
	glRotated(r,0,1,0);
	glRotor();
	glPopMatrix();
	r += speed;
}


void glShaft(void){
	glMaterialColor(ms_HandSpinner);
	glPushMatrix();
	glRotated(90,0,0,1);
	for(int j=0;j<2;++j){
		glTorus( 10.0,1.60,pow(-1,j)*4.25,0,0);
		glPipe(8.4,1.0,3.2,pow(-1,j)*4.25,0,0);
		glCylinder(7.4,2.8,pow(-1,j)*4.00,0,0);
		glCylinder( 10,1.6,pow(-1,j)*3.45,0,0);
		for(int i=0;i<3;++i){
			glPushMatrix();
			glRotated(i*120,0,0,0);
			glRectangular(0.4,3.0,0.5,pow(-1,j)*5.6,6,0);
			glPopMatrix();
		}
	}
	glPopMatrix();
}


void glRotor(void){
	glMaterialColor(ms_HandSpinner);
	glPushMatrix();
	glRotated(90,0,0,1);

	glPipe(11.5,5,5,0,0,0);
	glTorus(14,2.5,0,0,0);

	static double R = 22.0;
	for(int i=0;i<3;++i){
		glMaterialColor(ms_HandSpinner);
		double theta = (double)i*2.0/3.0*PI;
		glPipe(11.5,0.5,5,0,R*cos(theta),R*sin(theta));
		glTorus(14,2.5,0,R*cos(theta),R*sin(theta));

		glPushMatrix();
		glRotated(-90,0,0,1);
		glRotated(theta*180/PI+60,0,1,0);
		glRectangular(R/2,5,23,R/2,0,0);
		glCylinder(2.5,R,R/2,0, 11.5);
		glCylinder(2.5,R,R/2,0,-11.5);
		glPopMatrix();
		
		/* wight */
		glMaterialColor(ms_black_plastic);
		glPipe(11,6,5.2,0,R*cos(theta),R*sin(theta));
		glMaterialColor(ms_black_rubber);
		glPipe(11,1,5.5,0,R*cos(theta),R*sin(theta));
		glPipe( 6,1,5.5,0,R*cos(theta),R*sin(theta));
	}
	glPopMatrix();
}


int windowW = 0;
int windowH = 0;

/* Draw String Information */
void glDisplayStrings(void){
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, windowW, windowH, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	/* String */
	glColor3d(0.0,0.0,0.0);
	char disp[50];
	sprintf(disp,"speed : %+3.0f",speed);
	glDrawString(disp,10,15);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	
}

/*****************************/

#endif //"Object_h_"
