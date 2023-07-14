#include "Entity.h"

Point Entity::diff(Point p2, Point p1)
{
    Point result = { p2.x - p1.x, p2.y - p1.y, p2.z - p1.z };
    return result;
}

double Entity::euclideanDistanceSquare(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z);
}