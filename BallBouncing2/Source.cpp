#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include<string>
#include<sstream>
#include "RGBpixmap.h"

void OnDisplay();
void InitGraphics(int argc, char* argv[]);

RGBpixmap ball;
RGBpixmap border;
RGBpixmap brick; 
int X, Y; // cordinates fo the mouse
float cx = 400;	// ball position X
float bx = 320;	// Border position X && Y will always be 0 
float cy = 20;	// ball position Y
float cxspd = 10;	// Speed pos x of the ball
float cyspd = 10;	// Speed pos y of the ball
float brickX = 100; // X position of the image brick
float brickY = 100;	// Y position of the image brick
int chances = 3; // number of Chances
int score = 0; // The Score 
int numofb = 1;
bool hit = false;
bool MouseMoved = false;
bool MouseClicked = false;
bool fb = true;
float brickps[5][2];
int main(int argc, char* argv[]) {
	InitGraphics(argc, argv);
	return 0;
}
void print(int a) {
	// Shows The Score
	glColor3d(1.0, 0.0, 0.0);
	glRasterPos2f(650, 40);
	stringstream ss;
	ss << a;
	string s = "Score: " + ss.str();
	int len = s.length();
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
	}
	//Shows The Number of Chances
	glRasterPos2f(650, 70);
	stringstream ss2;
	ss2 << chances;
	string chance = "Chances left: " + ss2.str();
	for (int i = 0; i < chance.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, chance[i]);
	}

}
void quit() {
	if (fb) {
		int Win = glutCreateWindow("Bouncing Ball");
		glutDestroyWindow(Win);
		exit(0);

	}
}

void reset() {
	
	cx = 400;
	cy = 23;
	bx = 320;
}
void end() {
	
	
	glColor3d(1.0, 0.0, 0.0);
	glRasterPos2f(250, 80);
	string s = "Game over Try Again";
	int len = s.length();
	for (int i = 0; i < len; i++) {
		
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
	}
	sndPlaySound(TEXT("Lost.wav"), SND_ASYNC);
	glBegin(GL_LINE_LOOP);
	glColor3d(1, 0, 0);
	glVertex2f(290, 205);
	glColor3d(1, 1, 0);
	glVertex2f(390, 205);
	glColor3d(1, 1, 1);
	glVertex2f(390, 255);
	glColor3d(0, 1, 1);
	glVertex2f(290, 255);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3d(1, 0, 0);
	glVertex2f(290, 150);
	glColor3d(1, 1, 0);
	glVertex2f(390, 150);
	glColor3d(1, 1, 1);
	glVertex2f(390, 200);
	glColor3d(0, 1, 1);
	glVertex2f(290,200);
	glEnd();
	glColor3d(1.0, 0.0, 0.0);
	glRasterPos2f(300, 220);
	string s1 = "New Game";
	int len1 = s1.length();
	for (int i = 0; i < len1; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s1[i]);
	}
	glColor3d(1.0, 0.0, 0.0);
	glRasterPos2f(290, 165);
	string s2 = "Quit Game";
	int len2 = s2.length();
	for (int i = 0; i < len2; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s2[i]);
	}
	
	MouseMoved = false;
	MouseClicked = false;
	if (chances == 0 && X >= 290 && X <=390&& Y >= 205 && Y <= 255) {
		chances = 3;
		numofb = 1;
		hit = false;
		score = 0;
		reset();
	}
	if (chances == 0 && X >= 290 && X <= 390 && Y >= 100 && Y <= 200) {
		fb = true;
		quit();
	}
}

void WON() {


	
	glBegin(GL_LINE_LOOP);
	glColor3d(1, 0, 0);
	glVertex2f(290, 205);
	glColor3d(1, 1, 0);
	glVertex2f(390, 205);
	glColor3d(1, 1, 1);
	glVertex2f(390, 255);
	glColor3d(0, 1, 1);
	glVertex2f(290, 255);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3d(1, 0, 0);
	glVertex2f(290, 150);
	glColor3d(1, 1, 0);
	glVertex2f(390, 150);
	glColor3d(1, 1, 1);
	glVertex2f(390, 200);
	glColor3d(0, 1, 1);
	glVertex2f(290, 200);
	glEnd();
	glColor3d(1.0, 0.0, 0.0);
	glRasterPos2f(300, 225);
	string s1 = "New Game";
	int len1 = s1.length();
	for (int i = 0; i < len1; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s1[i]);
	}
	glColor3d(1.0, 0.0, 0.0);
	glRasterPos2f(250, 80);
	string s = "Congrats , You WON !!";
	int len = s.length();
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
	}
	glColor3d(1.0, 0.0, 0.0);
	glRasterPos2f(290, 165);
	string s2 = "Quit Game";
	int len2 = s2.length();
	for (int i = 0; i < len2; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s2[i]);
	}
	MouseMoved = false;
	MouseClicked = false;
	if (numofb == 0 && X >= 290 && X <= 390 && Y >= 205 && Y <= 255) {
		chances = 3;
		numofb = 1;
		hit = false;
		score = 0;
		reset();
	}
	if (numofb == 0 && X >= 290 && X <= 390 && Y >= 100 && Y <= 200) {
		fb = true;
		quit();
	}
	

}
void menu() {
	glBegin(GL_LINE_LOOP);
	glColor3d(1, 0, 0);
	glVertex2f(250, 150);
	glColor3d(1, 1, 0);
	glVertex2f(450, 150);
	glColor3d(1, 1, 1);
	glVertex2f(450, 200);
	glColor3d(0, 1, 1);
	glVertex2f(250, 200);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3d(1, 0, 0);
	glVertex2f(250, 250);
	glColor3d(1, 1, 0);
	glVertex2f(450, 250);
	glColor3d(1, 1, 1);
	glVertex2f(450, 300);
	glColor3d(0, 1, 1);
	glVertex2f(250, 300);
	glEnd();
	glColor3d(1.0, 1.0, 1.0);
	glRasterPos2f(300, 270);
	
	string s = "Start Game";
	int len = s.length();
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
	}
	glColor3d(1.0, 1.0, 1.0);
	glRasterPos2f(300, 170);
	string s2 = "QuitGame";
	int len2 = s2.length();
	for (int i = 0; i < len2; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s2[i]);
	}
	if (X >= 250 && X <= 450 && Y >= 250 && Y <= 300)
	{
		fb = false;
	}
}


void makeBricks()
{
	for (int i = 0; i < 5; i++)
	{
			glPixelZoom(0.5, 0.5);
			glRasterPos2i(brickps[i][0], brickps[i][1]);
			
			brickps[i][0] = {brickX + 66};
			brickps[i][1] = {brickY +66};
			brickX = +66;
			brickY =+ 66;
			
			/*glPixelZoom(0.5, 0.5);
			glRasterPos2i(brickps[i][0], brickps[i][1]);
			brick.draw();*/
	}
	brick.draw();
	for (int i = 0; i < 5; i++)
	{
		
			cout <<"Hey : " << brickps[i][1] << endl;
		
	}
}

void MouseX_Y(int x, int y)
{
	MouseMoved = true;
	bx = x;

}
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		MouseClicked = true;
		cout << "Mouse Clicked : " << x << " " << 480 - y << endl;
		X = x;
		Y = 480 - y;
	}
	
}


void movingCircle()
{
	glutMouseFunc(mouse);

	if (MouseMoved) {
		cx += cxspd;
		cy += cyspd;
	}
	// the Borders of the screen 
	if (cx + ball.nCols * 0.09 >= 800 || cx <= 0 && MouseMoved == true) {
		cxspd = cxspd * -1;
		sndPlaySound(TEXT("WAll.wav"), SND_ASYNC);

		//score += 100;
	}

	if (cy + ball.nRows * 0.09 >= 480 || cx + ball.nCols * 0.09 >= bx && cx <= bx + border.nCols * 0.5 && cy  <= 23 && MouseMoved == true) {
		cyspd = cyspd * -1;
		sndPlaySound(TEXT("WAll.wav"), SND_ASYNC);

		//score += 100;
	}

	if (cx + ball.nCols * 0.11 >= brickX && cx + ball.nCols * 0.11 <= brickX + brick.nCols * 0.5 && cy + ball.nRows * 0.11 >= brickY && cy + ball.nRows * 0.11 <= brickY + brick.nRows * 0.5&& hit == false)
			{
				cxspd = cxspd * -1;
				score += 100;
				hit = true;
				numofb--;
				sndPlaySound(TEXT("Brick.wav"), SND_ASYNC);
				Sleep(500);
			}
			
	if (cy + ball.nRows * 0.11 >= brickY && cy + ball.nRows * 0.11 <= brickY+ brick.nRows * 0.5 && cx + ball.nCols * 0.11 >= brickX&& cx + ball.nCols * 0.11 <= brickX + brick.nCols * 0.5 && hit == false)
	{
		cyspd = cyspd * -1;
		score += 100;
		hit = true;
		numofb--;
		Sleep(1000);
		sndPlaySound(TEXT("Brick.wav"), SND_ASYNC);

	}
	MouseClicked == true;
	if (cy <= 0 ) {
		MouseMoved = false;
				cx = 400;
				cy = 25;
				bx = 320;
				chances--;
			}
}
void InitGraphics(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 480);
	int Win = glutCreateWindow("ONE BRICK");
	ball.readBMPFile("basket.bmp");
	border.readBMPFile("border.bmp");
	brick.readBMPFile("brick.bmp");

	glutMotionFunc(MouseX_Y);
	glutMouseFunc(mouse);
	glutDisplayFunc(OnDisplay);
	glutIdleFunc(OnDisplay);
	glutMainLoop();
}
void SetTransformations() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 480);
}
void OnDisplay() {
	MouseClicked = false;

	if (fb) {

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		SetTransformations();
		glEnable(GL_TEXTURE_2D);
		menu();
		if (X >= 250 && X <= 450 && Y >=150  && Y <= 300 ) { quit(); }
		glutPostRedisplay();
	}
	else  {
		
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		SetTransformations();
		glEnable(GL_TEXTURE_2D);

		Sleep(5);
		if (chances != 0 || numofb != 0)
		{
			
			glPixelZoom(0.09, 0.09);
			glRasterPos2i(cx, cy);
			ball.draw();
			glPixelZoom(0.5, 0.5);
			glRasterPos2i(bx, 0);
			border.draw();
			movingCircle();
			glPixelZoom(0.5, 0.5);
			glRasterPos2i(brickX, brickY);
			if (!hit) {
				brick.draw();
			}
			//makeBricks();
			print(score);
			MouseClicked == true;
		}

		if (chances == 0 || chances <= 0) {
			chances = 0;
			end();
			
		}
		if (numofb == 0) {
			
			sndPlaySound(TEXT("Small Win.wav"), SND_ASYNC);
			WON();
		}

		if (MouseMoved == true && bx <= 480 && bx >= 0)
		{
			glPixelZoom(0.5, 0.5);
			glRasterPos2i(bx, 0);
			border.draw();

		}
	}
	
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
