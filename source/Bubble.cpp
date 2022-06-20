#include "Bubble.h"
#include "Glut.h"
#include "math.h"

#define PI 3.1415926535897932


void drawCircle(float centerX, float centerY, float r) {
	glBegin(GL_LINE_LOOP);
	float x, y, ang;
	for (int i = 0; i < 16; i++) {
		ang = 2.0f*PI*i / 16;
		x = centerX + r*cos(ang);
		y = centerY + r*sin(ang);
		glVertex2f(x, y);
	}
	glEnd();
}


Bubble::Bubble()
{
	radius = 0;
}

Bubble::Bubble(float x, float y, float r, float s, float ang)
{
	posX = x;
	posY = y;
	radius = r;
	speed = s;
	angle = ang;
	decay = 0.1;
}

Bubble::Bubble(float x, float y, float r, float s, float ang, float decay)
{
	posX = x;
	posY = y;
	radius = r;
	speed = s;
	angle = ang;
	Bubble::decay = decay;
}

void Bubble::drawBubble()
{
	drawCircle(posX, posY, radius);
}

bool Bubble::isFaded()
{
	return radius < 0.01;
}

void Bubble::moveBubble()
{
	posX += speed*cos(angle);
	posY += speed*sin(angle);
	radius -= decay;
}

float Bubble::getRadius()
{
	return radius;
}

