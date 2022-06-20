#pragma once

#include "Bubble.h"
#include "Bullet.h"

class Ship
{
	private:
		float posX, posY;
		float angle;
		float scaleFactor;
		bool keys[4]; // left, right, up, space
		float maxSpeed;

		float lastAngle;
		float thrustPercent;

		Bubble bubbles[100];
		int bPtr;
		int bGenTime;

		Bullet bullets[100];
		int bulletPtr;

		void rotateLeft(float ang);
		void rotateRight(float ang);
		void updatePosition();
		float speedFunction();
		void shoot();
		
	public:
		int shieldT;
		bool alive;
		Ship();
		void drawShip();
		void specialKeyFuncUp(int key);
		void specialKeyFuncDown(int key);
		void keyFunctionDown(unsigned char key);
		void keyFunctionUp(unsigned char key);
		void timerFunc();
		Bullet* getBullets();
		float getX();
		float getY();
		float getScale();
		void moveToCenter();
		
};

