#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <cstdio>

typedef struct {
	double x, y, z;
}Point;

typedef struct {
	GLfloat r, g, b;
}Color;

class Entity
{
public:
	Point location;
	Color color;
	Point diff(Point p2, Point p1);
	double euclideanDistanceSquare(Point p1, Point p2);
};

#endif