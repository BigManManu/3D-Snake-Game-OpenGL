#pragma once
#pragma warning(disable : 4430)
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
#include <string>
#include "Border.h"
#include "Snake.h"
#include "Bunny.h"
#include "Gui.h"
using namespace std;
#define EYE_Z 4.73
#define DNEAR 0
#define SPEED 0.005
#define GROW_WHEN_EAT 25
#define INITIAL_LENGTH 0.5
#define INITIAL_Z 2
Border border;
Snake snake;
ColorPattern color;
Point up;
Bunny bunny(snake);
Gui gui;
int eaten = 0;
int width, height;
bool debug = false;
bool spawnGoldenBunny = false;
bool defaultCamera = true;
bool moving = false, gameover = false;
float x = 0.0, y = 0.0;
float deltaXMove = 0.0, deltaYMove = 0.0;
float scaleFactor = 1, rotateX = 0, rotateY = 0, rotateZ = 0;
double bunnyRotDegree = 0;
const int font = (int)GLUT_BITMAP_TIMES_ROMAN_24;