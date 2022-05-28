#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include"RGBpixmap.h"

RGBpixmap pix[4];
RGBpixmap marioR;
RGBpixmap marioL;


double TX = 0;
double TY = 0;
double Rz = 1;

UINT prevFrameTime = -1;
float currXPosition = 0;

/**
Creates the main window, registers event handlers, and
initializes OpenGL stuff.
*/
void InitGraphics(int argc, char *argv[]);

/**
Sets the logical coordinate system we will use to specify
our drawings.
*/
void SetTransformations();

/**
Handles the paint event. This event is triggered whenever
our displayed graphics are lost or out-of-date.
ALL rendering code should be written here.
*/
void OnDisplay();

void OnSpecialKeyPress(int key , int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT://		Left function key
		
		pix[0]=marioL;
		TX -= 4;
		break;
	case GLUT_KEY_RIGHT://		Right function key
		
		pix[0]=marioR;
		TX += 4;
		break;
	case GLUT_KEY_UP://		Jump function key
		TY += 20;
		break;
	};
}

void Draw_Cordinates()
{
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	// X-axis
	glVertex3f(-100, 0, 0);
	glVertex3f(100, 0, 0);
	//Y-axis
	glVertex3f(0, -100, 0);
	glVertex3f(0, 100, 0);
	glEnd();
}
void Update()
{
	UINT currTime = GetTickCount();
	//the first update?
	if (prevFrameTime == -1) {
		prevFrameTime = currTime;
		return;
	}
	float dt = (currTime - prevFrameTime) / 1000.0;

	
		Rz-= 30 * dt;
	
	prevFrameTime = currTime;

}

int main(int argc, char* argv[]) {
	InitGraphics(argc, argv);
	return 0;
}

/**
Creates the main window, registers event handlers, and
initializes OpenGL stuff.
*/
void InitGraphics(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	//Create an 800x600 window with its top-left corner at pixel (100, 100)
	glutInitWindowPosition(0, 0); //pass (-1, -1) for Window-Manager defaults
	glutInitWindowSize(1350, 700);
	glutCreateWindow("OpenGL Lab");

	marioR.readBMPFile("marioR.bmp");
	marioL.readBMPFile("marioL.bmp");
	pix[0] = marioR;
	
	pix[1].readBMPFile("Home.bmp");
	pix[2].readBMPFile("Block.bmp");

	pix[3].readBMPFile("sun.bmp");

	glutSpecialFunc(OnSpecialKeyPress);
	//OnDisplay will handle the paint event
	glutDisplayFunc(OnDisplay);
	glutIdleFunc(OnDisplay);
	glutMainLoop();
}

/**
Sets the logical coordinate system we will use to specify
our drawings.
*/
void SetTransformations() {
	//set up the logical coordinate system of the window: [-100, 100] x [-100, 100]
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 200, 0, 200);
}

/**
Handles the paint event. This event is triggered whenever
our displayed graphics are lost or out-of-date.
ALL rendering code should be written here.
*/
void OnDisplay() {
	//set the background color to white
	glClearColor(1, 1, 1, 1);
	//fill the whole color buffer with the clear color
	glClear(GL_COLOR_BUFFER_BIT);
	
	SetTransformations();
	
	Draw_Cordinates();
	
	

	//Blocks
	glPixelZoom(1,1);
	glRasterPos2i(0, 0);
	pix[2].draw();

	//Home
	glPixelZoom(0.75, 0.75);
	glRasterPos2i(170, 0);
	pix[1].draw();

	// Mario
	glEnable(GL_TEXTURE_2D);
	glPixelZoom(0.3, 0.3);
	glRasterPos2i(TX, TY);
	pix[0].draw();
	Sleep(100);
	TY = 0;
	
	//Sun
	glPixelZoom(1, 1);
	glRasterPos2i(0, 160);
	pix[3].draw();
	


	//TX+=0.01;
	//force previously issued OpenGL commands to begin
	//execution
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
