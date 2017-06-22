#ifndef Object_h_
#define Object_h_

/*****************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<GL/glut.h>

#include"MyGLUT.h"
#include"Colors.h"
#include"Define.h"

/* clock time */
clock_t tstart = clock();
clock_t tstop  = tstart;

/* parameters for camera */
double dstnc = 100.0;
double theta =  0*PI/180;
double phi   = 50*PI/180;
double xc    = 0.0;
double yc    = 0.0;
double zc    = 0.0;

/* rotation speed */
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
		glCylinder(10,1.60,pow(-1,j)*3.45,0,0);
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

	glPipe(11,6,5,0,0,0);

	static double R = 22.0;
	for(int i=0;i<3;++i){
		glMaterialColor(ms_HandSpinner);
		double theta = (double)i*2.0/3.0*PI;
		glPipe(11.5,0.5,5,0,R*cos(theta),R*sin(theta));
		glTorus(14,2.5,0,R*cos(theta),R*sin(theta));

		glPushMatrix();
		glRotated(-90,0,0,1);
		glRotated(theta*180/PI+60,0,1,0);
		glRectangular(R/2,5,18,R/2,0,0);
		glPopMatrix();
		
		int max = 30;
		for(double j=0;j<=max;++j){
			glPushMatrix();
			glRotated(-90,0,0,1);
			glRotated(theta*180/PI-30,0,1,0);
			glTranslated(0,0,15);
			glRotated(-40+80.0*j/max,0,1,0);
			glCylinder(2.5,25,0,0,-3.9);
			glPopMatrix();
		}
		
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
	glColor3d(1.0,1.0,1.0);
	char s[50];
	sprintf(s,"speed    : %+6.1f  (arrow key Right,Left)",speed);
	glDrawString3(s,20,30);
	if(speed) tstop = clock();
	sprintf(s,"time     : %5.2f sec",(double)(tstop-tstart)/CLOCKS_PER_SEC);
	glDrawString(s,20,60);
	sprintf(s,"distance : %+6.1f (arrow key Up,Down)",dstnc);
	glDrawString(s,20,75);
	sprintf(s,"angle    : %+6.1f %+6.1f",theta*180/PI,phi*180/PI);
	glDrawString(s,20,90);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	
}

/*****************************/

#endif //"Object_h_"
