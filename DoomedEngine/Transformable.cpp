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