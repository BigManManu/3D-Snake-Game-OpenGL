#include "Gui.h"

void Gui::GameHud(void* font, int score)
{
	std::string text = "Score: " + std::to_string(score);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2f(0.05, 0.05);
	for (auto i = 0; i < text.length(); i++)
		glutBitmapCharacter(font, text[i]);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Gui::DebugHud(void* font, Snake& snake)
{
	int last_index = (snake.firstIndex + snake.bodySegments) % MAX_SEGMENTS;
	std::string coord = "x: " + std::to_string(snake.snakeBody[last_index].x);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2f(0.05, 0.1);
	for (auto i = 0; i < coord.length(); i++)
		glutBitmapCharacter(font, coord[i]);
	coord = "y: " + std::to_string(snake.snakeBody[last_index].y);
	glRasterPos2f(0.05, 0.13);
	for (auto i = 0; i < coord.length(); i++)
		glutBitmapCharacter(font, coord[i]);
	coord = "z: " + std::to_string(snake.snakeBody[last_index].z);
	glRasterPos2f(0.05, 0.16);
	for (auto i = 0; i < coord.length(); i++)
		glutBitmapCharacter(font, coord[i]);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}