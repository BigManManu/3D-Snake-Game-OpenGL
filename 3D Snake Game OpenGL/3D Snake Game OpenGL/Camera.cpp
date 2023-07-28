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