#ifndef LOADER_CLASS_H
#define LOADER_CLASS_H
#include <gl/glut.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

class Loader
{
public:
	static void eatline(std::istream& input);
	void load_model(const char file[], std::vector<GLfloat>& vertices, std::vector<GLuint>& faces, std::vector<GLfloat>& normals);
};

#endif