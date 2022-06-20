#include "Legend.h"
#include "Glut.h"
#include "math.h"

Legend::Legend()
{
	score = 0;
	lives = 3;
	level = 1;
}

double cbrt(double arg) {
	return pow(arg, 1.0 / 3);
}

void drawHeart() {
	glBegin(GL_POLYGON);
	for (float x = -1.139; x <= 1.139; x += 0.001)
	{
		float delta = cbrt(x*x) * cbrt(x*x) - 4 * x*x + 4;
		float y1 = (cbrt(x*x) + sqrt(delta)) / 2;
		float y2 = (cbrt(x*x) - sqrt(delta)) / 2;
		glVertex2f(x, y1);
		glVertex2f(x, y2);
	}
	glEnd();

}

char* intToCharArr(int num) {
	char *nums = new char[10];
	int k = 9;
	while (num != 0) {
		nums[k--] = '0' + (num % 10);
		num = num / 10;
	}
	nums[k] = 27;
	return nums;
}

void Legend::drawLegend()
{
	for (int i = 0; i < lives; i++) {
		glPushMatrix();
		glTranslatef(50 + i*40, 550, 0);
		glScalef(15, 15, 1);
		drawHeart();
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(200, 545, 0);
	glScalef(0.2, 0.2, 1);
	char scoreTxt[] = "SCORE: ";
	for (int i = 0; i < 9; i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, scoreTxt[i]);
	}
	glPopMatrix();

	glPushMatrix();
	char *scoreString = intToCharArr(score);
	glTranslatef(300, 545, 0);
	glScalef(0.2, 0.2, 1);
	if (score == 0) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, '0');
	}
	else {
		int k = 0;
		while (scoreString[k] != 27) k++;
		for (int i = k; i < 10; i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, scoreString[i]);
		}
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(600, 545, 0);
	glScalef(0.2, 0.2, 1);
	char levelsTxt[] = "LEVEL: ";
	for (int i = 0; i < 7; i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, levelsTxt[i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(700, 545, 0);
	glScalef(0.2, 0.2, 1);
	char *levelString = intToCharArr(level);
	int k = 0;
	while (levelString[k] != 27) k++;
	for (int i = k; i < 10; i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, levelString[i]);
	}
	glPopMatrix();

}

void Legend::drawScore()
{
	glPushMatrix();
	char *scoreString = intToCharArr(score);
	if (score == 0) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, '0');
	}
	else {
		int k = 0;
		while (scoreString[k] != 27) k++;
		for (int i = k; i < 10; i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, scoreString[i]);
		}
	}
	glPopMatrix();
}

