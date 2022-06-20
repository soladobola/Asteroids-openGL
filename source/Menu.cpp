#include "Menu.h"
#include "Glut.h"



Menu::Menu(Legend* legend)
{
	option = 0;
	enable = true;
	end = false;
	restartSignal = false;
	Menu::legend = legend;
}

void Menu::drawMenu()
{
	char arr[] = "ASTEROIDS";
	char startString[] = "START GAME";
	char exitString[] = "EXIT";
 	glPushMatrix();
	glTranslatef(60, 400, 0);
	for (int i = 0; i < 9; i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, arr[i]);
	}

	glPopMatrix();
	glPushMatrix();
	glTranslatef(300, 250, 0);
	glScalef(0.25, 0.25, 1);
	for(int i = 0; i < 10; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, startString[i]);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(360, 170, 0);
	glScalef(0.25, 0.25, 1);
	for (int i = 0; i < 4; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, exitString[i]);

	glPopMatrix();

	//240
	float yoffset = 260;
	if (option == 1) yoffset = 175;

	glPushMatrix();
	glTranslatef(230, yoffset, 0);
	glScalef(25, 25, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(-1, -0.5);
	glVertex2f(-1, 0.5);
	glVertex2f(1, 0);
	glEnd();

	glPopMatrix();
}

void Menu::drawEndMenu()
{
	char arr[] = "GAME OVER";
	char startString[] = "PLAY AGAIN";
	char scoreString[] = "SCORE: ";
	char exitString[] = "EXIT";
	glPushMatrix();
	glTranslatef(70, 400, 0);
	glScalef(0.8, 0.8, 1);
	for (int i = 0; i < 9; i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, arr[i]);
	}

	glPopMatrix();

	glPushMatrix();
	glTranslatef(280, 300, 0);
	glScalef(0.3, 0.3, 1);
	for (int i = 0; i < 7; i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, scoreString[i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(430, 300, 0);
	glScalef(0.3, 0.3, 1);
	(*legend).drawScore();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(300, 200, 0);
	glScalef(0.25, 0.25, 1);
	for (int i = 0; i < 10; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, startString[i]);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(360, 120, 0);
	glScalef(0.25, 0.25, 1);
	for (int i = 0; i < 4; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, exitString[i]);

	glPopMatrix();

	float yoffset = 210;
	if (option == 1) yoffset = 120;

	glPushMatrix();
	glTranslatef(230, yoffset, 0);
	glScalef(25, 25, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(-1, -0.5);
	glVertex2f(-1, 0.5);
	glVertex2f(1, 0);
	glEnd();

	glPopMatrix();



}

void Menu::keyDownFunc(unsigned char key)
{

	if (key == 13) {

		if (option == 0) {
			if(enable == true)
			enable = false;
			if (end == true) {
				restartSignal = true;
			}
		}

		if (option == 1 && (enable == true || end == true)) {
			exit(0);
		}
	}
}

void Menu::specialKeyDownFunc(int key)
{
	
	if (key == GLUT_KEY_UP) {
		option = 0;
	}
	else if (key == GLUT_KEY_DOWN) {
		option = 1;
	}
}

bool Menu::isEnabled()
{
	return enable;
}
