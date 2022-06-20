
#pragma once
class Bubble
{
	private:
		float posX, posY;
		float radius;
		float speed;
		float angle;
		float decay;
	public:
		Bubble();
		Bubble(float x, float y, float r, float s, float ang);
		Bubble(float x, float y, float r, float s, float ang, float decay);
		void drawBubble();
		bool isFaded();
		void moveBubble();
		float getRadius();
		
};

