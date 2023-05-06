#include "openGLPart.h"

void cameraPos(float& cameraX, float& cameraY, float& cameraZ, Point dir) {
	cameraX = snakeBody[(bodySegments + firstIndex) % MAX_SEGMENTS].x;
	cameraY = snakeBody[(bodySegments + firstIndex) % MAX_SEGMENTS].y;
	cameraZ = snakeBody[(bodySegments + firstIndex) % MAX_SEGMENTS].z;
	if (dir.x != 0) {
		cameraX += 5.0;
		dir.x < 0 ? cameraX *= -1 : cameraX *= 1;
	}
	else if (dir.y != 0) {
		cameraY += 5.0;
		dir.y < 0 ? cameraY *= -1 : cameraY *= 1;
	}
	else if (dir.z != 0) {
		cameraZ += 5.0;
		dir.z < 0 ? cameraZ *= -1 : cameraZ *= 1;
	}
}