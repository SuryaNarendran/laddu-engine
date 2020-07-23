#pragma once
#include "DOOM.h"

class Shader {

public:
	GLuint programID;
	GLuint modelViewID;
	GLuint projectionID;

	Shader(GLuint _programID, GLuint _modelViewID, GLuint _projectionID);
	Shader();
};