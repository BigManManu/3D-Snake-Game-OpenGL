#ifndef SNAKE_CLASS_H
#define SNAKE_CLASS_H
#include <GL/glut.h>
#include "Entity.h"
#include "Shapes.h"
#define MAX_SEGMENTS 1000
#define INITIAL_Z 2
#define INITIAL_LENGTH 0.5
#define TAIL_THICKNESS 0.25
#define THICKNESS 0.03 
#define NUMBER_OF_BUNNIES 10
#define BUNNY_SIZE 0.1

class Snake : public Entity
{
private:
	Shapes shape;
	double length(double r);

public:
	int score;
	Point snakeBody[MAX_SEGMENTS];
	ColorPattern color;
	Point snakeUp;
	int bodySegments;
	int firstIndex;
	int lats = 30;
	int longs = 200;
	Snake();
	void render(double r, double tailR, ColorPattern color, Point snakeUp);
	int eatsBunny(Point bunnyLoaction[], bool &isGoldenBunny, Snake &snake);
	bool snakeCrossesItself();
};

#endif