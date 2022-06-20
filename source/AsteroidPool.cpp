#include "stdlib.h"
#include "AsteroidPool.h"
#include "time.h"
#include "math.h"

#define PI 3.1415926535897932


int seeds[] = { 858,922,653,248,419,948,99,612,422,322,435,859,38,765,430,304,946,987,891,339,745,
				995,76,160,495,865,59,287,902,502,709,489,239,194,258,187,234,137,35,719,595,498,515,663,530,839,
				981,951,301,640,735,111,933,563,256,572,912,586,854,209,603,403,101,841,143,276,327,582,210,199,982,806,
				880,353,500,870,377,275,964,121,446,139,372,691,465,242,413,130,655,25,298,55,54,511,171,354,459,648,345,299 };

AsteroidPool::AsteroidPool(int size, Legend* legend)
{
	poolSize = size;
	asters = new Asteroid[poolSize];
	bPtr = 0;
	level = 1;
	AsteroidPool::legend = legend;
	endSignal = false;
	gameStartedSignal = false;
	generateNewLevel(1);
}

void AsteroidPool::drawAsteroids()
{
	for (int i = 0; i < poolSize; i++) {
		if(asters[i].isAlive())
			asters[i].drawAsteroid();
	}

	// Draw bubbles
	for (int i = 0; i < 100; i++) {
		if (!bubbles[i].isFaded()) {
			bubbles[i].moveBubble();
			bubbles[i].drawBubble();
		}
	}
}


void AsteroidPool::collisionAnimation(float x, float y)
{
	float angle;
	float size = 15;
	float sp = 1;
	float decay = 1.2;

	for (int i = 0; i < 5; i++) {
		srand(time(0) + i*324234);
		angle = (((float)rand()) / RAND_MAX)*2.0f*PI;
		bubbles[bPtr] = Bubble(x, y, size, sp, angle, decay);
		bPtr = (bPtr + 1) % 100;
	}
	

}

void AsteroidPool::moveAsteroids()
{
	for (int i = 0; i < poolSize; i++) {
		if(asters[i].isAlive())
			asters[i].moveAsteroid();
	}

}

bool AsteroidPool::allClear()
{
	for (int i = 0; i < poolSize; i++) {
		if (asters[i].isAlive()) return false;
	}

	return true;
}

void AsteroidPool::addAsteroid(Asteroid aster)
{
	for (int i = 0; i < poolSize; i++) {
		if (!asters[i].isAlive()) {
			asters[i] = aster;
			break;
		}
	}
}



void AsteroidPool::generateNewLevel(int level)
{
	
	int asterNum = level * 2;	
	float ang;
	
	for (int i = 0; i < asterNum; i++) {
		ang = (((float)rand()) / RAND_MAX)*2.0f*PI;
		
		AsteroidPool::addAsteroid(*(new Asteroid( 400 + 400*cos(ang), 300 + 300*sin(ang), 3, 100, time(0) + seeds[i]*seeds[i])));
		
	}
}

void AsteroidPool::BulletCollisionHandler(Bullet * arr, int bsize)
{
	for (int i = 0; i < poolSize; i++) {
		if (!asters[i].isAlive()) continue;
			
		for (int j = 0; j < bsize; j++) {	
			if (arr[j].isFaded()) continue;
			if (asters[i].bulletCollision(arr[j])) {
				// update pool, score
				asters[i].alive = false;
				arr[j].distance = 1000;
				collisionAnimation(asters[i].posX, asters[i].posY);

				(*(legend)).score += 50;

				if (asters[i].size == 1) {
					if (allClear()) {
						AsteroidPool::level += 1;
						generateNewLevel(AsteroidPool::level);
						(*(legend)).level += 1;
					}
					continue;
				}

				Asteroid child1(asters[i].posX, asters[i].posY, asters[i].size - 1, asters[i].scaleFactor / 2, time(0) + seeds[(i + 13)%100]*3);
				Asteroid child2(asters[i].posX, asters[i].posY, asters[i].size - 1, asters[i].scaleFactor / 2, time(0) + seeds[(i + 61) % 100] * 7);
				AsteroidPool::addAsteroid(child1);
				AsteroidPool::addAsteroid(child2);

			}
		}
	}
}

void AsteroidPool::shipCollisionHandler(Ship* ship)
{	
	if ((*ship).shieldT > 0) return;
	for (int i = 0; i < poolSize; i++) {
		if (!asters[i].isAlive()) continue;

		if (asters[i].shipCollision(*ship)) {
			asters[i].alive = false;
			collisionAnimation((*ship).getX(), (*ship).getY());
			collisionAnimation(asters[i].posX, asters[i].posY);
			
			(*(legend)).lives--;
			(*ship).shieldT = 120;
			(*ship).moveToCenter();
			if ((*(legend)).lives == 0) {
				endSignal = true;
				AsteroidPool::gameStartedSignal = false;
			}
			
			if (asters[i].size == 1) {
				if (allClear()) {
					AsteroidPool::level += 1;
					generateNewLevel(AsteroidPool::level);
					(*(legend)).level += 1;
				}
				continue;
			}

			Asteroid child1(asters[i].posX, asters[i].posY, asters[i].size - 1, asters[i].scaleFactor / 2, time(0) + seeds[(i + 7) % 100] * 11);
			Asteroid child2(asters[i].posX, asters[i].posY, asters[i].size - 1, asters[i].scaleFactor / 2, time(0) + seeds[(i + 53) % 100] * 23);
			AsteroidPool::addAsteroid(child1);
			AsteroidPool::addAsteroid(child2);
		}

	}
}
