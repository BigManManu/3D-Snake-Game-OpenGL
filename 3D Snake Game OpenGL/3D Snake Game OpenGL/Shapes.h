#ifndef SHAPES_CLASS_H
#define SHAPES_CLASS_H
#include <GL/glut.h>
#include <math.h>
#define M_PI 3.141592653589

enum ColorPattern {
    CHECKERED,
    V_STRIPPED,
    H_STRIPPED,
    SOLID,
    SOLID_WHITE,
    SOLID_BLACK,
    NO_COLOR
};

class Shapes
{
private:
    void eyeBall(double rx, double ry, double rz, int lats, int longs, ColorPattern color, ColorPattern frontColor, bool orientation);
public:
    void head(double rx, double r, int lats, int longs, ColorPattern color);
    void cone(int lats, int longs, double r1, double r2, double L, ColorPattern color);
    void torus(int lats, int longs, double fromTheta, double toTheta, double r1, double r2,
        double R, ColorPattern color, double r0, double tail, double tailRange, double headRange, double rx);
};

#endif 
