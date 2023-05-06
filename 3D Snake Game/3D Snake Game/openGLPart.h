#pragma once
#include<gl/glut.h>
#include<math.h>
#include <iostream>
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
using namespace std;
#define M_PI 3.141592653589
#define EYE_Z 4.73
#define DNEAR 0
#define TAIL 0.2
#define TAIL_THICKNESS 0.25//25% of the original thickness... 0.0075
#define NUM_OF_BUNNIES 1000
#define GROW_WHEN_EAT 25
#define END 0.01
#define INITIAL_LENGTH 0.5
#define MAX_SEGMENTS 1000
#define BLINKING_PERIOD 100
#define FIELD_DEPTH 3
#define INITIAL_Z 2
#define LOW_RES 1
using namespace std;
using std::vector;

enum ColorPattern {
    CHECKERED,
    V_STRIPPED,
    H_STRIPPED,
    SOLID,
    SOLID_WHITE,
    SOLID_BLACK,
    NO_COLOR
};

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};
typedef struct {
    double x, y, z;
}Point;

typedef struct {
    GLfloat r, g, b;
}BunnyColor;

extern double BUNNY_SIZE;
extern BunnyColor bunnyColor;
extern int NUMBER_OF_BUNNIES;
extern double SPEED;
extern double THICKNESS;
extern double xRot, yRot, zRot;
extern ColorPattern color;
extern Point snakeBody[MAX_SEGMENTS];
extern int bodySegments, lats, longs;
extern GLfloat randomColors[300000];
extern std::vector<GLfloat> vertices;
extern std::vector<GLuint> faces;
extern std::vector<GLfloat> normals;
extern int firstIndex;
extern Point bunnyLocation[NUM_OF_BUNNIES];
Point diff(Point p2, Point p1);
void torus(int lats, int longs, double fromTheta, double toTheta, double r1, double r2, double R, ColorPattern color, double r0, double tail, double tailRange, double headRange, double rx);
void cone(int lats, int longs, double r1, double r2, double L, ColorPattern color);
void head(double rx, double r, int lats, int longs, ColorPattern color);
void eyeBall(double rx, double ry, double rz, int lats, int longs, ColorPattern color, ColorPattern frontColor, bool orientation);
double length(double r);
double euclideanDistanceSquare(Point p1, Point p2);
Point randomBunnyLocation(int x, int y, int z, int max, int except);
void load_bunny_data(const char file[], std::vector<GLfloat>& vertices, std::vector<GLuint>& faces, std::vector<GLfloat>& normals);
void bunny(double size, Point loc);
void conicSnake(double r, double tailR, ColorPattern color, Point snakeUp);
bool snakeCrossesItself();
int eatsBunny();
void cameraPos(float& cameraX, float& cameraY, float& cameraZ, Point dir);