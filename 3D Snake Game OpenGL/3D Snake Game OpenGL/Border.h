#ifndef BRODER_CLASS_H
#define BORDER_CLASS_H
#include <GL/glut.h>

class Border
{
public:
	void cube(double depth);
private:
	typedef GLint vertex3[3];
	vertex3 pt[8] = { {-1, -1, -1}, {-1, 1, -1}, {1, -1, -1}, {1, 1, -1},
	{-1, -1, 1}, {-1, 1, 1}, {1, -1, 1}, {1, 1, 1} };
	void quad(GLint n1, GLint n2, GLint n3, GLint n4, double depth);
};

#endif 