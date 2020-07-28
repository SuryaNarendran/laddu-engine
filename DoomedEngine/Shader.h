#pragma once
#include "DOOM.h"

class Shader {

public:
	GLuint programID;
	GLuint modelViewID;
	GLuint projectionID;
	GLuint transformID;
	GLuint lightPositionID;
	GLuint ambientProductID;
	GLuint diffuseProductID;
	GLuint specularProductID;

	Shader(GLuint _programID);
	Shader();
};