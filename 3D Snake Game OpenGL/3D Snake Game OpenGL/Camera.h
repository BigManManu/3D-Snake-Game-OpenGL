#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H
#include <GL/glut.h>
#include "Snake.h"

class Camera
{
private:
	float cameraX, cameraY, cameraZ;
public:
	void WorldCamera(double eyeX, double eyeY, double eyeZ, double centerX, double centerY);
	void FirstPersonCamera(Snake& snake);
};

#endif