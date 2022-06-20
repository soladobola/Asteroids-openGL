#include "Ship.h"
#include "Glut.h" 
#include "math.h"
#include <stdio.h>


#define PI 3.1415926535897932


Ship::Ship() {
	
	alive = true;
	angle = 0;
	lastAngle = 0;
	scaleFactor = 25;
	posX = 400;
	posY = 300;
	thrustPercent = 0;
	maxSpeed = 4;

	bPtr = 0;
	bGenTime = 5;

	bulletPtr = 0;
	shieldT = 0;
	

	keys[0] = false;
	keys[1] = false;
	keys[2] = false;
	keys[3] = false;
	
}

void Ship::drawShip() {
	
	// draw bubbles and bullets
	for (int i = 0; i < 100; i++) {

		if (!bubbles[i].isFaded()) {
			bubbles[i].moveBubble();
			bubbles[i].drawBubble();
		}

		if (!bullets[i].isFaded()) {
			bullets[i].moveBullet();
			bullets[i].drawBullet();
		}
	}

	if (shieldT > 0) {
		glPushMatrix();
		float x, y, a;
		glTranslatef(posX, posY, 0);
		glScalef(scaleFactor, scaleFactor, 1);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 32; i++) {
			a = 2.0f*PI*i / 32;
			glVertex2f(cos(a), sin(a));
		}
		glEnd();
		glPopMatrix();
		shieldT--;
	}
	
	glPushMatrix();
	glTranslatef(Ship::posX, Ship::posY, 0);
	glScalef(scaleFactor, scaleFactor, 1);
	glRotatef(angle*180/PI, 0, 0, 1);
	
	glBegin(GL_LINES);
	glVertex2f(-0.5,-0.5);
	glVertex2f(0, 0.5);
	
	glVertex2f(0, 0.5);
	glVertex2f(0.5, -0.5);

	
	glVertex2f(-0.25, 0);
	glVertex2f(0.25, 0);

	glTranslatef(-Ship::posX, -Ship::posY, 0);

	glEnd();
	glPopMatrix();

	

}


void Ship::specialKeyFuncUp(int key)
{
	switch (key) {

		case GLUT_KEY_LEFT:
			keys[0] = false;
			break;

		case GLUT_KEY_RIGHT:
			keys[1] = false;
			break;

		case GLUT_KEY_UP:
			keys[2] = false;
			lastAngle = angle;
			break;

	}
}

void Ship::specialKeyFuncDown(int key)
{
	switch (key) {

	case GLUT_KEY_LEFT:
		keys[0] = true;
		break;

	case GLUT_KEY_RIGHT:
		keys[1] = true;
		break;
	case GLUT_KEY_UP:
		keys[2] = true;
		break;

	}
}

void Ship::keyFunctionDown(unsigned char key)
{
	if (key == ' ') {
		bullets[bulletPtr] = Bullet(posX + 10 * cos(angle + PI / 2), 
									posY + 10 * sin(angle + PI / 2), 
									2.5, 10, angle + PI / 2);

		bulletPtr = (bulletPtr + 1) % 100;
	}
}

void Ship::keyFunctionUp(unsigned char key)
{
}

void Ship::timerFunc()
{
	if (keys[0]) {
		rotateLeft(0.1);
	}

	if (keys[1]) {
		rotateRight(0.1);
	}

	if (keys[2]) {
		if (thrustPercent <= 1)
			thrustPercent += 0.1;
		else
			thrustPercent = 1;

		// generete bubbles

		if (bGenTime == 0) {
			Bubble bubble(posX, posY, 5, 3, angle - PI/2);
			bubbles[bPtr] = bubble;
			bPtr = (bPtr + 1) % 100;
			bGenTime = 5;
		}

	}
	else {

		if(thrustPercent > 0)
		thrustPercent -= 0.01;
		else thrustPercent = 0;
	}

	if (bGenTime > 0)
		bGenTime -= 1;

	updatePosition();

}

Bullet * Ship::getBullets()
{
	return bullets;
}

float Ship::getX()
{
	return posX;
}

float Ship::getY()
{
	return posY;
}

float Ship::getScale()
{
	return scaleFactor;
}

void Ship::moveToCenter()
{
	posX = 400;
	posY = 300;
}

void Ship::shoot() {

}

void Ship::rotateLeft(float ang) {
	Ship::angle += ang;
}

void Ship::rotateRight(float ang) {
	Ship::angle += -ang;
}

void Ship::updatePosition()
{
	float ang = angle;
	if (!keys[2]) ang = lastAngle;
	
	posX += maxSpeed*speedFunction()*cos(ang + PI/2);
	posY += maxSpeed*speedFunction()*sin(ang + PI/2);

	if (posX > 800) {
		posX = 0;
	}

	if (posX < 0) {
		posX = 800;
	}

	if (posY > 600){
		posY = 0;
	}
	if (posY < 0) {
		posY = 600;
	}
}

// Returns percent of max speed
float Ship::speedFunction()
{

	float fmax = 5;

		
	return 0.5*(log10((thrustPercent*fmax) + 0.1) + 1);
	
}
