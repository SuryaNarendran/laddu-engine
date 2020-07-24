#pragma once
#include "DOOM.h"

class Shader {

public:
	GLuint programID;
	GLuint modelViewID;
	GLuint projectionID;
	GLuint transformID;

	Shader(GLuint _programID, GLuint _modelViewID, GLuint _projectionID, GLuint _transformID);
	Shader();
};