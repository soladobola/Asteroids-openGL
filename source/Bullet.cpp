#include "Glut.h"
#include "math.h"
#include "Bullet.h"


#define PI 3.1415926535897932


Bullet::Bullet()
{
	distance = 1000;
}

void fillCircle(float centerX, float centerY, float r) {
	glBegin(GL_POLYGON);
	float x, y, ang;
	for (int i = 0; i < 16; i++) {
		ang = 2.0f*PI*i / 16;
		x = centerX + r*cos(ang);
		y = centerY + r*sin(ang);
		glVertex2f(x, y);
	}
	glEnd();
}

Bullet::Bullet(float x, float y, float r, float s, float ang)
{
	posX = x;
	posY = y;
	radius = r;
	speed = s;
	angle = ang;
	distance = 0;
}

void Bullet::drawBullet()
{
	fillCircle(posX, posY, radius);
}

void Bullet::moveBullet()
{
	posX += speed*cos(angle);
	posY += speed*sin(angle);

	distance += 10;

	if (posX > 800) {
		distance = 1000;
	}
	else if (posX < 0) {
		distance = 1000;
	}

	if (posY > 600 ) {
		distance = 1000;
	}
	else if (posY < 0) {
		distance = 1000;
	}
}

bool Bullet::isFaded()
{
	return distance > 800;
}
