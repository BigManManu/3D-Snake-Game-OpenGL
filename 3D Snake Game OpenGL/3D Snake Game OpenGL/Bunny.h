#ifndef BUNNY_CLASS_H
#define BUNNY_CLASS_H
#include "Entity.h"
#include "Loader.h"
#include "Snake.h"
#include <vector>
#define NUMBER_OF_BUNNIES 10
#define BUNNY_SIZE 0.1
#define FIELD_DEPTH 3

class Bunny: public Entity
{
private:
	Color bunnyColor;
	Color goldenBunnyColor;
	Loader loader;
	const char* filename = "bunny-low-res.obj";
public:
	Point bunnyLocation[NUMBER_OF_BUNNIES+1];
	std::vector<GLfloat> vertices;
	std::vector<GLuint> faces;
	std::vector<GLfloat> normals;
	Bunny(Snake snake);
	Point generateRandomLocation(int x, int y, int z, int max, int except, Snake& snake);
	void render(double size, Point loc, bool isGolden);
	void load();
};

#endif