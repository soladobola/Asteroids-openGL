#pragma once

#include "Point.h"
#include "Bullet.h"
#include "Ship.h"

class Asteroid {

public:
	float posX, posY;
	float scaleFactor;
	float angle;
	float speed;
	int size;
	bool alive;	
	Point vertex[10];
	
	Asteroid();
	Asteroid(float x, float y, float size, float sf, unsigned int seed);
	void drawAsteroid();
	void moveAsteroid();
	bool isAlive();
	bool bulletCollision(Bullet b);
	bool shipCollision(Ship ship);


};
