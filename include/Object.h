#ifndef Object_h_
#define Object_h_

/*****************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#ifdef __APPLE__
#include<GLUT/glut.h>
#endif

#ifdef linux
#include<gl/glut.h>
#endif

#include"MyGLUT.h"
#include"Colors.h"
#include"Hue2rgb.h"
#include"Define.h"

/* status flag */
bool SFLAG = true;

/* clock time */
clock_t tstart = 0; // for rotation timer
clock_t tnow   = 0; // for rotation timer
clock_t FrameTbase = 0;   // for frame rate
int FrameCounter   = 0;   // for frame rate
int TmpCounter     = 0;   // for frame rate
double FrameTimer  = 0.0; // for frame rate

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
		/* handle grip */
		glTorus( 10.0,1.60,pow(-1,j)*4.25,0,0);
		glCylinder(8.4,3.2,pow(-1,j)*4.25,0,0);
		glCylinder(10-1e-2,1.6,pow(-1,j)*3.45,0,0);	
	}
	glPopMatrix();
}


void glRotor(void){
	glMaterialColor(ms_HandSpinner);
	glPushMatrix();
	glRotated(90,0,0,1);
	/* foundation */
	glPipe(11,6,5,0,0,0);
	static double R = 23.0;
	for(int i=0;i<3;++i){
		glMaterialColor(ms_HandSpinner);
		double theta = (double)i*2.0/3.0*PI;
		/* wheel */
		glPipe(11.5,0.5,5,0,R*cos(theta),R*sin(theta));
		glTorus( 14.0,2.5,0,R*cos(theta),R*sin(theta));
		/* plane */
		glPushMatrix();
		glRotated(-90,0,0,1);
		glRotated(theta*180/PI+60,0,1,0);
		glRectangular(R/2,5,15,R/2,0,0);
		glPopMatrix();
		/* curve */
		int smooth = 50;
		for(double j=0;j<=smooth;++j){
			glPushMatrix();
			glRotated(-90,0,0,1);
			glRotated(theta*180/PI-30,0,1,0);
			glTranslated(6.0*(+smooth-2*j)/smooth,0,15);
			glRotated(  84.5*(-smooth+2*j)/smooth,0,1,0);
			glCylinder(2.5,10-4.0*pow((smooth-2*j)/smooth,2),0,0,-3.9);
			glPopMatrix();
		}
		/* wight */
		glMaterialColor(ms_black_plastic);
		glPipe(10,4,5.1,0,R*cos(theta),R*sin(theta));
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
		
		FrameTimer = (double)(clock()-FrameTbase)/CLOCKS_PER_SEC;
		if(FrameTimer>=1.0){
			TmpCounter = FrameCounter;
			FrameCounter = 0;
			FrameTbase = clock();
		}
		++FrameCounter;
		/* Strings */
		glColor3d(1.0,1.0,1.0);
		static char s[128];
		sprintf(s,"speed    : %5.1f rpm",fabs(speed)*TmpCounter/6.0);
		glDrawString(s,25,15);
		if(speed) tnow = clock();
		sprintf(s,"time     : %5.1f sec",(double)(tnow-tstart)/CLOCKS_PER_SEC);
		glDrawString(s,25,30);
		sprintf(s,"frame    : %5d fps",TmpCounter);
		glDrawString(s,25,45);
		sprintf(s,"distance : %5.0f mm",dstnc);
		glDrawString(s,25,60);
		sprintf(s,"angle    : %+4.0f %+3.0f",theta*180/PI,phi*180/PI);
		glDrawString(s,25,75);

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
	static double doff = 0.10;
	static double aoff = 0.05;
	static double diff = 0.15;
	static double ambi = 0.10;
	hue2rgb hue(x,windowW);
	ms_HandSpinner.diffuse[0] = doff+diff*hue.R();
	ms_HandSpinner.ambient[0] = aoff+ambi*hue.R();
	ms_HandSpinner.diffuse[1] = doff+diff*hue.G();
	ms_HandSpinner.ambient[1] = aoff+ambi*hue.G();
	ms_HandSpinner.diffuse[2] = doff+diff*hue.B();
	ms_HandSpinner.ambient[2] = aoff+ambi*hue.B();
}


/*****************************/

#endif //"Object_h_"
