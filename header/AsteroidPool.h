#pragma once

#include "Asteroid.h"
#include "Bubble.h"
#include "Legend.h"

class AsteroidPool {

private:
	int poolSize;
	int asterLeft;
	Asteroid *asters;
	Bubble bubbles[100];
	int bPtr;
	void collisionAnimation(float x, float y);
	Legend* legend;
	int level;
	
public:
	bool endSignal;
	bool gameStartedSignal;
	AsteroidPool(int size, Legend* legent);
	void drawAsteroids();
	void moveAsteroids();
	bool allClear();
	void addAsteroid(Asteroid aster);
	void generateNewLevel(int level);
	void BulletCollisionHandler(Bullet* arr, int bsize);
	void shipCollisionHandler(Ship* ship);

};