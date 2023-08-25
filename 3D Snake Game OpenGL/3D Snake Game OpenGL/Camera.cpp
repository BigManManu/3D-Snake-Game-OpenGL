#include "Camera.h"

void Camera::WorldCamera(double eyeX, double eyeY, double eyeZ, double centerX, double centerY)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, (GLfloat)800 / (GLfloat)800, 0.005, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        eyeX, eyeY, eyeZ,
        centerX, centerY, 0.0,
        0.0, 1.0, 0.0);
}

void Camera::FirstPersonCamera(Snake& snake)
{
    Point dir = snake.diff(snake.snakeBody[(snake.bodySegments + snake.firstIndex) % (MAX_SEGMENTS)],
        snake.snakeBody[(snake.firstIndex + snake.bodySegments - 1) % (MAX_SEGMENTS)]);
    cameraX = snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS].x;
    cameraY = snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS].y;
    cameraZ = snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS].z;
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
    double X, Y, Z;
    X = snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS].x,
    Y = snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS].y,
    Z = snake.snakeBody[(snake.bodySegments + snake.firstIndex) % MAX_SEGMENTS].z,
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, (GLfloat)800 / (GLfloat)800, 0.005, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        X, Y, Z,
        cameraX, cameraY, cameraZ,
        0.0, 1.0, 0.0);
}