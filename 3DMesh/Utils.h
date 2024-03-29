#ifndef UTILS_H
#define UTILS_H
#include <GL/freeglut.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits>
#define LEFT 1
#define RIGHT 2

typedef std::vector<GLfloat> floatvec;

static GLfloat centerX = 0.0, centerY = 0.0, centerZ = 0.0;
//const GLfloat floralWhite[] = { 1.0, 0.988, 0.949 };
//const GLfloat paleSilver[] = { 0.80, 0.773, 0.725 };
//const GLfloat blackOlive[] = { 0.251, 0.239, 0.224 };
//const GLfloat eerieBlack[] = { 0.145, 0.141, 0.133 };
void drawAxis();
floatvec crossProduct(floatvec& a, floatvec& b);
GLfloat dotProduct(floatvec& a, floatvec& b);
void normalize(floatvec& vec);
floatvec normalizedGet(floatvec& vec);
#endif