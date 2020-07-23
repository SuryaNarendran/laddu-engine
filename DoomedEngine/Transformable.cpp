#include "Transformable.h"

Transformable::Transformable() {
	position = glm::vec4(0, 0, 0, 1);
	eulerAngles = glm::vec3(0, 0, 0);
	scale = glm::vec4(1, 1, 1, 0);
}

glm::mat4 Transformable::GetTransformMatrix() {
	
	glm::mat4 retval = translate(glm::mat4(1.0f), glm::vec3(position));

	retval = rotate(retval, eulerAngles[2], glm::vec3(0, 0, 1));
	retval = rotate(retval, eulerAngles[1], glm::vec3(0, 1, 0));
	retval = rotate(retval, eulerAngles[0], glm::vec3(1, 0, 0));

	retval = glm::scale(retval, glm::vec3(scale));

	return retval;
}

void Transformable::Translate(GLfloat x, GLfloat y, GLfloat z) {
	position += glm::vec4(x, y, z, 0);
}

void Transformable::Rotate(GLfloat xAxis, GLfloat yAxis, GLfloat zAxis) {
	eulerAngles += glm::vec3(xAxis, yAxis, zAxis);
}

void Transformable::Scale(GLfloat x, GLfloat y, GLfloat z) {
	scale += glm::vec4(x, y, z,0);
}

void Transformable::Translate(glm::vec3 values) {
	position += glm::vec4(values,0.0f);
}

void Transformable::Rotate(glm::vec3 values) {
	eulerAngles += values;
}

void Transformable::Scale(glm::vec3 values) {
	scale += glm::vec4(values, 0.0f);
}