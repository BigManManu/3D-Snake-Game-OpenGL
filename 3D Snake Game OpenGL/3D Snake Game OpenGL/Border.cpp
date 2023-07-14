#include "Border.h"

void Border::cube(double depth)
{
    glColor4f(0.6, 0.6, 0.6, .5);
    glNormal3f(0, 0, -1);
    quad(2, 0, 1, 3, depth);//FLOOR, Z=0
    glColor4f(0.0, 1.0, 1.0, 0.5);
    glNormal3f(-1, 0, 0);
    quad(5, 1, 0, 4, depth);//X=0
    glColor4f(0.0, 0.0, 1.0, 0.5);//BLUE
    glNormal3f(0, 1, 0);
    quad(7, 3, 1, 5, depth);//Y=100
    glColor4f(1.0, 1.0, 0.0, 0.5);
    glNormal3f(0, -1, 0);
    quad(4, 0, 2, 6, depth);//Y=0
    glColor4f(1.0, 0.0, 1.0, .5);//GREEN
    glNormal3f(1, 0, 0);
    quad(6, 2, 3, 7, depth);//X=100
}

void Border::quad(GLint n1, GLint n2, GLint n3, GLint n4, double depth)
{
    glBegin(GL_QUADS);
    glVertex3f(pt[n1][0], pt[n1][1], (pt[n1][2] + 1) * depth / 2 - 1);
    glVertex3f(pt[n2][0], pt[n2][1], (pt[n2][2] + 1) * depth / 2 - 1);
    glVertex3f(pt[n3][0], pt[n3][1], (pt[n3][2] + 1) * depth / 2 - 1);
    glVertex3f(pt[n4][0], pt[n4][1], (pt[n4][2] + 1) * depth / 2 - 1);
    glEnd();
}