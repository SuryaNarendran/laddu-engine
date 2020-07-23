#include "Transformable.h"

Transformable::Transformable() {
	position = vec4(0, 0, 0, 1);
	eulerAngles = vec3(0, 0, 0);
	scale = vec4(1, 1, 1, 0);
}

mat4 Transformable::GetTransformMatrix() {
	
	mat4 retval = translate(mat4(1.0f), vec3(position));

	retval = rotate(retval, eulerAngles[2], vec3(0, 0, 1));
	retval = rotate(retval, eulerAngles[1], vec3(0, 1, 0));
	retval = rotate(retval, eulerAngles[0], vec3(1, 0, 0));

	retval = glm::scale(retval, vec3(scale));

	return retval;
}