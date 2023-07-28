#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H
#include <GL/glut.h>

class Camera
{
public:
	void WorldCamera(double eyeX, double eyeY, double eyeZ, double centerX, double centerY);
};

#endif