/* main.cpp
*	
*	main source program for
*	simulation of Hand Spinner (Fidget Spinner)
*		(c) S.Suzuki 2017.1.23
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#include<glut.h>
#include<Object.h>

bool MFLAG = false; /* Mouse Flag */
bool CFLAG = false; /* Color Bar Mode */

/* Function Prototype Declaration */
void Window(void);
void PopUpMenu(void);
void Controler(void);
void init(void);
void idle(void);
void display(void);
void resize(int w, int h);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void menu(int val);
void keyboard(unsigned char key, int x, int y);
void keyboard_sp(int key, int x, int y);
void SetCamera(void);
void AngleReset(void);


/* main function */
int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	Window();
	PopUpMenu();
	Controler();
	glutMainLoop();
	return 0;
}


/******** Functions *********/

void Window(void){
	glutInitWindowPosition(0,0);
	glutInitWindowSize(300,250);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Hand Spinner");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	init();
}


void PopUpMenu(void){
	glutCreateMenu(menu);
	glutAddMenuEntry("Change Color",3);
	glutAddMenuEntry("Show Status",2);
	glutAddMenuEntry("Reset Angle",1);
	glutAddMenuEntry("Quit",0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void Controler(void){
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard_sp);
}


void init(void){
	glClearColor( 0.1, 0.1, 0.1, 1.0 );
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glLightInit();
	AngleReset();
}


void idle(void){
	glutPostRedisplay();
}


void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLightSetting();

	/* draw objects */
	if(CFLAG) glColorBar();
	glHandSpinner();
	glDisplayStrings();
	glDisplayButtons();

	/* dynamic friction */
	static double dspeed = 0.002;
	if(speed){
		if( 0.1<speed)      speed -= dspeed;
		else if(speed<-0.1) speed += dspeed;
		else speed = 0.0;
	}

	glutSwapBuffers();
}


void resize(int w, int h){
	windowW = w;
	windowH = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, w/(double)h, 1.0, 1000.0);
	SetCamera();
}


/* mouse click */
void mouse(int button, int state, int x, int y){
	static double dspeed = 5.0;
	static double max    = 60.0;
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if(state==GLUT_UP){
				MFLAG = false;
				if(CFLAG) CFLAG = false;
			}
			if(state==GLUT_DOWN){
				if(CFLAG) SetSpinnerColor(x);
				else{
					static double ButtonSize = 20;
					double XbuttonR = windowW-ButtonSize;
					double XbuttonL = ButtonSize;
					if(XbuttonR<=x){
						if(0<=speed){
							tstart = clock();
							speed += dspeed;
							if( max<speed) speed = max;
						}
						else speed = 0.0;
					}
					if(x<=XbuttonL){
						if(speed<=0){
							tstart = clock();
							speed -= dspeed;
							if(speed<-max) speed = -max;
						}
						else speed = 0.0;
					}
				}
			}
			break;
		default:
			break;
	}
	glutIdleFunc(idle);
}


/* mouse motion */
void motion(int x, int y){
	const double Rspeed = 0.2; /* Angle Rotate Speed */
	static int xmouse;
	static int ymouse;
	if(MFLAG){
		if(CFLAG) SetSpinnerColor(x);
		else{ /* Angle Rotate */
			theta += (xmouse-x)*PI/180*Rspeed;
			if(theta>2*PI) theta -= 2*PI;
			if(theta<0)    theta += 2*PI;
			phi +=-(ymouse-y)*PI/180*Rspeed;
			if(phi> PI*2/5) phi = PI*2/5;
			if(phi<-PI*2/5) phi =-PI*2/5;
			SetCamera();
		}
	}
	glutIdleFunc(idle);
	xmouse = x;
	ymouse = y;
	MFLAG  = true;
}


void menu(int val){
	switch(val){
		case 0: /* Quit */
			printf("\n");
			exit(0);
		case 1: /* Camera Reset */
			AngleReset();
			break;
		case 2: /* Status Information */
			if(SFLAG) SFLAG = false;
			else SFLAG = true;
			break;
		case 3: /* Color Bar */
			if(CFLAG) CFLAG = false;
			else CFLAG = true;
			break;
		default:
			break;
	}
	glutIdleFunc(idle);
}


void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 'q': /* Quit */
			printf("\n");
			exit(0);
		case '_': /* Camera Reset */
			AngleReset();
			break;
		case 's': /* Status Information */
			if(SFLAG) SFLAG = false;
			else SFLAG = true;
			break;
		case 'c': /* Color Bar */
			if(CFLAG) CFLAG = false;
			else CFLAG = true;
			break;
		default:
			break;
	}
	glutIdleFunc(idle);
}


void keyboard_sp(int key, int x, int y){
	double dDstnc = dstnc/50;
	double dspeed = 0.2;
	static double max = 60.0;
	switch(key){
		case GLUT_KEY_RIGHT:
			tstart = clock();
			speed += dspeed;
			if( max<speed) speed = max;
			break;
		case GLUT_KEY_LEFT:
			tstart = clock();
			speed -= dspeed;
			if(speed<-max) speed = -max;
			break;
		case GLUT_KEY_UP:
			dstnc -= dDstnc;
			if(dstnc<40) dstnc = 40;
			SetCamera();
			break;
		case GLUT_KEY_DOWN:
			dstnc += dDstnc;
			if(dstnc>700) dstnc = 700;
			SetCamera();
			break;
		default:
			break;
	}
	glutIdleFunc(idle);
}


void SetCamera(void){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	double ex = xc+dstnc*cos(phi)*sin(theta);
	double ey = yc+dstnc*sin(phi);
	double ez = zc+dstnc*cos(phi)*cos(theta);
	gluLookAt(ex,ey,ez,xc,yc,zc,0,1,0);
}


void AngleReset(void){
	dstnc = 80.0;
	theta =  0.0;
	phi   = PI/4;
	SetCamera();
}
