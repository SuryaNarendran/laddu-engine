// an object with a defined position in 3D space
#pragma once
#include "DOOM.h"

class Transformable{

public:
	vec4 position;
	vec3 eulerAngles;
	vec4 scale;

public:

	mat4 GetTransformMatrix();
	void Translate(GLfloat x, GLfloat y, GLfloat z);
	void Rotate(GLfloat xAxis, GLfloat yAxis, GLfloat zAxis);
	void Scale(GLfloat x, GLfloat y, GLfloat z);
	Transformable();
};
