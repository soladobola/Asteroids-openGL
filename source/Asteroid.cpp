
#include "stdlib.h"
#include "Asteroid.h"
#include "Glut.h"
#include "math.h"


#define PI 3.1415926535


bool circleCollision(float x1, float y1, float r1, float x2, float y2, float r2 ) {
	float distance = sqrtf((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	return distance <= r1 + r2;
}

bool Asteroid::bulletCollision(Bullet b)
{
	return circleCollision(posX, posY, scaleFactor, b.posX, b.posY, b.radius);
}

bool Asteroid::shipCollision(Ship ship)
{
	return circleCollision(posX, posY, scaleFactor - scaleFactor/3.5, ship.getX(), ship.getY(), scaleFactor / 2);
}

Asteroid::Asteroid()
{
	alive = false;
}

Asteroid::Asteroid(float x, float y, float s, float sf, unsigned int seed)
{
	posX = x;
	posY = y;
	size = s;
	scaleFactor = sf;
	alive = true;

	float smallR = 0.6;
	float bigR = 1;
	srand(seed);
	//Random angle
	angle = rand() / float(RAND_MAX);
	angle *= 2.0f*PI;
	if (fabsf(cos(angle)) < 0.1 || fabsf(sin(angle)) < 0.1) angle += 0.6;
	

	speed = (((float)rand()) / (float)RAND_MAX) + 1.5;


	float ang, dist;
	for (int i = 0; i < 10; i++) {
		ang = 2.0f*PI*i / 10;
		dist = rand() / float(RAND_MAX);
		dist = dist*smallR + (bigR - smallR);
		vertex[i] = Point(cos(ang)*dist, sin(ang)*dist);
	}


}

void Asteroid::drawAsteroid()
{
	glPushMatrix();
	glTranslatef(posX, posY, 0);
	glScalef(scaleFactor, scaleFactor, 1);
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 10; i++) {
		glVertex2f(vertex[i].x, vertex[i].y);
	}

	glEnd();
	glPopMatrix();
	
}

void Asteroid::moveAsteroid()
{
	posX += speed*cos(angle);
	posY += speed*sin(angle);

	if (posX > 800 + scaleFactor) {
		posX = -scaleFactor;
	}
	else if (posX < -scaleFactor) {
		posX = 800 + scaleFactor;
	}

	if (posY > 600 + scaleFactor) {
		posY = -scaleFactor;
	}
	else if (posY < -scaleFactor) {
		posY = 600 + scaleFactor;
	}
}

bool Asteroid::isAlive()
{
	return alive;
}
