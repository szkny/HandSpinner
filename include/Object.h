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
#include"Hue2rgb.h"
#include"Define.h"

/* status flag */
bool SFLAG = true;

/* clock time */
clock_t tstart = clock();
clock_t tnow   = tstart;

/* current window size */
int windowW = 0;
int windowH = 0;

/* parameters for camera */
double dstnc,theta,phi;
double xc,yc,zc;

/* rotation speed */
double speed = 0.0;

/* prototype decleration */
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
		/* grip */
		glTorus( 10.0,1.60,pow(-1,j)*4.25,0,0);
		glPipe(8.4,1.0,3.2,pow(-1,j)*4.25,0,0);
		glCylinder(7.4,2.8,pow(-1,j)*4.00,0,0);
		glCylinder(10-1e-2,1.6,pow(-1,j)*3.45,0,0);	
		/* pattern */
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
	/* foundation */
	glPipe(11,6,5,0,0,0);
	static double R = 22.0;
	for(int i=0;i<3;++i){
		glMaterialColor(ms_HandSpinner);
		double theta = (double)i*2.0/3.0*PI;
		/* wheel */
		glPipe(11.5,0.5,5,0,R*cos(theta),R*sin(theta));
		glTorus(14,2.5,0,R*cos(theta),R*sin(theta));
		/* plane */
		glPushMatrix();
		glRotated(-90,0,0,1);
		glRotated(theta*180/PI+60,0,1,0);
		glRectangular(R/2,5,16,R/2,0,0);
		glPopMatrix();
		/* curve */
		int max = 50;
		for(double j=0;j<=max;++j){
			glPushMatrix();
			glRotated(-90,0,0,1);
			glRotated(theta*180/PI-30,0,1,0);
			glTranslated(3.5*(+max-2*j)/max,0,15);
			glRotated(  58.0*(-max+2*j)/max,0,1,0);
			glCylinder(2.5,10-2.0*pow((max-2*j)/max,2),0,0,-3.9);
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


/* Draw String Information */
void glDisplayStrings(void){
	if(SFLAG){
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
		sprintf(s,"speed    : %+6.1f",speed);
		glDrawString3(s,25,30);
		if(speed) tnow = clock();
		sprintf(s,"time     : %5.2f sec",(double)(tnow-tstart)/CLOCKS_PER_SEC);
		glDrawString(s,25,60);
		sprintf(s,"distance : %+6.1f",dstnc);
		glDrawString(s,25,75);
		sprintf(s,"angle    : %+6.1f %+6.1f",theta*180/PI,phi*180/PI);
		glDrawString(s,25,90);

		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_LIGHTING);
	}	
}

/* Draw Buttons */
void glDisplayButtons(void){
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, windowW, windowH, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	/* Speed Setting Button */
	static double ButtonSize    = 20.0;
	static double DirectionSize = 10.0;
	double up = windowH*(DirectionSize/2.0+0.5)/DirectionSize;
	double dw = windowH*(DirectionSize/2.0-0.5)/DirectionSize;
	double R = windowW-ButtonSize;
	double L = ButtonSize;
	glColor3d(0.5,0.5,0.5);
	glBegin(GL_TRIANGLES);
	glVertex2d(R+1,dw);
	glVertex2d(R+1,up);
	glVertex2d(windowW-1,windowH/2.0);
	glVertex2d(1,windowH/2.0);
	glVertex2d(L-1,up);
	glVertex2d(L-1,dw);
	glEnd();

	glColor3d(1.0,1.0,1.0);
	glBegin(GL_QUADS);
	glVertex2d(R,0);
	glVertex2d(windowW,0);
	glVertex2d(windowW,windowH);
	glVertex2d(R,windowH);
	glVertex2d(0,0);
	glVertex2d(L,0);
	glVertex2d(L,windowH);
	glVertex2d(0,windowH);
	glEnd();

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
}


void glColorBar(void){
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, windowW, windowH, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	double hmax = windowW;
	double hbin = hmax/1000;
	int i = 0;
	glBegin(GL_QUADS);
	for(double h=0.0;h<hmax;h+=hbin){
		hue2rgb hue(h,hmax);
		glColor3d(hue.R(),hue.G(),hue.B());
		glVertex2d(h     ,windowH-20);
		glVertex2d(h+hbin,windowH-20);
		glVertex2d(h+hbin,windowH);
		glVertex2d(h     ,windowH);
		++i;
	}
	glEnd();

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
}


void SetSpinnerColor(int x){
	hue2rgb hue(x,windowW);
	ms_HandSpinner.diffuse[0] = 0.10+0.20*hue.R();
	ms_HandSpinner.ambient[0] = 0.05+0.05*hue.R();
	ms_HandSpinner.diffuse[1] = 0.10+0.20*hue.G();
	ms_HandSpinner.ambient[1] = 0.05+0.05*hue.G();
	ms_HandSpinner.diffuse[2] = 0.10+0.20*hue.B();
	ms_HandSpinner.ambient[2] = 0.05+0.05*hue.B();
}


/*****************************/

#endif //"Object_h_"
