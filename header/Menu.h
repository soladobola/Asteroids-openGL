#pragma once
#include "Legend.h"

class Menu {

private:
	int option;
	Legend* legend;

public:
	bool enable;
	bool restartSignal;
	bool end;
	Menu(Legend* legend);
	void drawMenu();
	void drawEndMenu();
	void keyDownFunc(unsigned char key);
	void specialKeyDownFunc(int key);
    bool isEnabled();
	
};
