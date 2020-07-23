// an object with a defined position in 3D space
#pragma once
#include "DOOM.h"

class Transformable{

public:
	glm::vec4 position;
	glm::vec3 eulerAngles;
	glm::vec4 scale;

public:

	glm::mat4 GetTransformMatrix();
	void Translate(GLfloat x, GLfloat y, GLfloat z);
	void Rotate(GLfloat xAxis, GLfloat yAxis, GLfloat zAxis);
	void Scale(GLfloat x, GLfloat y, GLfloat z);
	void Translate(glm::vec3 values);
	void Rotate(glm::vec3 values);
	void Scale(glm::vec3 values);
	Transformable();
};
