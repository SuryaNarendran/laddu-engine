//main header file for Pseudo-Doom project

#pragma once

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif //M_PI

#ifdef __APPLE__  // include Mac OS X verions of headers
#  include <OpenGL/OpenGL.h>
#  include <GLUT/glut.h>
#else // non-Mac OS X operating systems
#  include <GL/glew.h>
#  include <GL/glut.h>
#  include <GL/freeglut.h>
#  include <GL/freeglut_ext.h>

#endif  // __APPLE__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#define RAD_TO_DEG 57.295779
#define DEG_TO_RAD 0.01745 //make more precise?

#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 800
#define FLOAT_EPSILON 0.000001f
#define CHAR_TO_INT 48


// Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))


