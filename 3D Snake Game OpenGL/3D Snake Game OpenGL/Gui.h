#ifndef GUI_CLASS_H
#define GUI_CLASS_H
#include <gl/glut.h>
#include <string>
#include <iostream>
#include "Snake.h"

class Gui
{
public:
	void GameHud(void* font, int score);
	void DebugHud(void* font, Snake& snake);
};

#endif