
#include <math.h>		
#include <stdio.h>
#include <stdlib.h>		
#include "Glut.h"
#include "Ship.h"
#include "Bubble.h"
#include "Asteroid.h"
#include "AsteroidPool.h"
#include "Menu.h"
#include "Legend.h"

const double Xmin = 0.0, Xmax = 800.0;
const double Ymin = 0.0, Ymax = 600.0;

#define PI 3.1415926535



Ship ship;
Legend legend;
Menu menu(&legend);
AsteroidPool asterPool(100, &legend);



bool running = false;



void drawRect(float x, float y, float w, float h) {
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y - h);
	glVertex2f(x, y - h);
	glEnd();
}


void myKeyboardUpFunc(unsigned char key, int x, int y)
{
	ship.keyFunctionUp(key);

}

void myKeyboardDownFunc(unsigned char key, int x, int y)
{
	menu.keyDownFunc(key);
	ship.keyFunctionDown(key);

}

void mySpecialKeyUpFunc(int key, int x, int y)
{
	ship.specialKeyFuncUp(key);
}

void mySpecialKeyDownFunc(int key, int x, int y)
{
	menu.specialKeyDownFunc(key);
	ship.specialKeyFuncDown(key);
}

void drawBoundaries() {
	drawRect(0, 600, 800, 3);
	drawRect(0, 3, 800, 3);

	drawRect(0, 600, 3, 600);
	drawRect(797, 600, 3, 600);
	
}



void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	drawBoundaries();
	if (!(asterPool.gameStartedSignal)) {
		menu.end = asterPool.endSignal;
		if (!menu.end)
			menu.drawMenu();
		else
			menu.drawEndMenu();
	}
	else {
		legend.drawLegend();
		ship.drawShip();
		asterPool.drawAsteroids();
		asterPool.moveAsteroids();
		asterPool.BulletCollisionHandler(ship.getBullets(), 100);
		asterPool.shipCollisionHandler(&ship);
	}
	 
	

	glFlush();
	glutSwapBuffers();
	
}


void resizeWindow(int w, int h)
{
	double scale, center;
	double windowXmin, windowXmax, windowYmin, windowYmax;

	glViewport(0, 0, w, h);

	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;
	if ((Xmax - Xmin) / w < (Ymax - Ymin) / h) {
		scale = ((Ymax - Ymin) / h) / ((Xmax - Xmin) / w);
		center = (Xmax + Xmin) / 2;
		windowXmin = center - (center - Xmin)*scale;
		windowXmax = center + (Xmax - center)*scale;
		windowYmin = Ymin;
		windowYmax = Ymax;
	}
	else {
		scale = ((Xmax - Xmin) / w) / ((Ymax - Ymin) / h);
		center = (Ymax + Ymin) / 2;
		windowYmin = center - (center - Ymin)*scale;
		windowYmax = center + (Ymax - center)*scale;
		windowXmin = Xmin;
		windowXmax = Xmax;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(windowXmin, windowXmax, windowYmin, windowYmax, -1, 1);

	glMatrixMode(GL_MODELVIEW);

}



void timer(int) {

	if (menu.restartSignal) {
		ship = *(new Ship());
		legend = *(new Legend());
		menu = *(new Menu(&legend));
		asterPool = *(new AsteroidPool(100, &legend));
		running = true;
		asterPool.gameStartedSignal = true;
		menu.enable = false;

	}

	if (!menu.isEnabled()) {
		if (running == false) {
			asterPool.gameStartedSignal = true;
			running = true;
		}
		ship.timerFunc();
	}
	
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
}

void initRendering()
{
	timer(0);
	glLineWidth(2);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(10, 60);
	glutInitWindowSize(800,600);

	glutCreateWindow("Asteroids by Mladen");

	initRendering();

	glutKeyboardFunc(myKeyboardDownFunc);
	glutKeyboardUpFunc(myKeyboardUpFunc);
	
	glutSpecialUpFunc(mySpecialKeyUpFunc);
	glutSpecialFunc(mySpecialKeyDownFunc);

	glutReshapeFunc(resizeWindow);
	glutDisplayFunc(drawScene);
	
	glutMainLoop();

	return(0);
}

