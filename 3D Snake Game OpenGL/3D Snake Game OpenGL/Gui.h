#ifndef GUI_CLASS_H
#define GUI_CLASS_H
#include <gl/glut.h>
#include <string>
#include <iostream>
#include "Snake.h"

class Gui
{
public:
	static void GameHud(void* font, int score);
	static void GameHud(GLfloat x, GLfloat y, void* font, const char* str);
	static void DebugHud(void* font, Snake& snake);
};

#endif