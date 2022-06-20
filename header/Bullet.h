#pragma once

class Bullet {
	public:
		float posX, posY;
		float radius;
		float speed;
		float angle;
		float distance;
	
		Bullet();
		Bullet(float x, float y, float r, float s, float ang);
		void drawBullet();
		void moveBullet();
		bool isFaded();

};
