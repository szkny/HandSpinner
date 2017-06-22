/* main.cpp
*
*	Simulation of Hand Spinner (Fidget Spinner)
*		(c) S.Suzuki 2017.1.23
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>

#include<GL/glut.h>
#include<Object.h>

bool MFLAG = false;

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


/* main function */
int main(int argc, char *argv[]){
	glutInit(&argc, argv);

	/* animation window */
	Window();
	PopUpMenu();
	Controler();

	glutMainLoop();
	return 0;
}


/******** Functions *********/

void Window(void){
	glutInitWindowPosition(900,0);
	glutInitWindowSize(600,450);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Fidget Spinner");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	init();
}


void PopUpMenu(void){
	glutCreateMenu(menu);
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
	glClearColor( 0.8, 0.8, 0.8, 1.0 );

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glLightInit();
}


void idle(void){
	glutPostRedisplay();
}


void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLightSetting();
	glHandSpinner();
	glDisplayStrings();
	glutSwapBuffers();
}


void resize(int w, int h){
	windowW = w;
	windowH = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, w/(double)h, 1.0, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	double ex = xc+dstnc*cos(phi)*sin(theta);
	double ey = yc+dstnc*sin(phi);
	double ez = zc+dstnc*cos(phi)*cos(theta);
	gluLookAt(ex,ey,ez,xc,yc,zc,0,1,0);
}


/* mouse click */
void mouse(int button, int state, int x, int y){
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if(state==GLUT_UP){
				MFLAG = false;
			}
			if(state==GLUT_DOWN){
				;
			}
			glutIdleFunc(idle);
			break;
		default:
			break;
	}
}


/* mouse motion */
void motion(int x, int y){
	const double Rspeed = 0.2; /* Rotate Speed */
	static int xmouse;
	static int ymouse;
	if(MFLAG){
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		theta += (xmouse-x)*PI/180*Rspeed;
		if(theta>2*PI) theta -= 2*PI;
		if(theta<0)    theta += 2*PI;
		phi +=-(ymouse-y)*PI/180*Rspeed;
		if(phi> PI*4/10) phi = PI*4/10;
		if(phi<-PI*4/10) phi =-PI*4/10;
		double ex = xc+dstnc*cos(phi)*sin(theta);
		double ey = yc+dstnc*sin(phi);
		double ez = zc+dstnc*cos(phi)*cos(theta);
		gluLookAt(ex,ey,ez,xc,yc,zc,0,1,0);
	}
	glutIdleFunc(idle);
	xmouse = x;
	ymouse = y;
	MFLAG  = true;
}


void menu(int val){
	switch(val){
		case 0:  /* Quit */
			exit(0);
		default:
			break;
	}
}


void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 'q': /* Quit */
			exit(0);
		default:
			break;
	}
}


void keyboard_sp(int key, int x, int y){
	double ex,ey,ez;
	double dDstnc = dstnc/50;
	double dspeed = 1.0;
	switch(key){
		case GLUT_KEY_RIGHT:
			if(speed< 60) speed += dspeed;
			break;
		case GLUT_KEY_LEFT:
			if(-60<speed) speed -= dspeed;
			break;
			break;
		case GLUT_KEY_UP:
			dstnc -= dDstnc;
			if(dstnc<10) dstnc = 10;
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			ex = xc+dstnc*cos(phi)*sin(theta);
			ey = yc+dstnc*sin(phi);
			ez = zc+dstnc*cos(phi)*cos(theta);
			gluLookAt(ex,ey,ez,xc,yc,zc,0,1,0);
			glutIdleFunc(idle);
			break;
		case GLUT_KEY_DOWN:
			dstnc += dDstnc;
			if(dstnc>700) dstnc = 700;
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			ex = xc+dstnc*cos(phi)*sin(theta);
			ey = yc+dstnc*sin(phi);
			ez = zc+dstnc*cos(phi)*cos(theta);
			gluLookAt(ex,ey,ez,xc,yc,zc,0,1,0);
			glutIdleFunc(idle);
			break;
		default:
			break;
	}
}


