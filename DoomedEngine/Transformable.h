// an object with a defined position in 3D space
#pragma once
#include "DOOM.h"

class Transformable{

public:
	vec4 position;
	vec3 eulerAngles;
	vec4 scale;

public:

	//mat4 GetTransformMatrix();
	Transformable() {
		position = vec4(0, 0, 0, 1);
		eulerAngles = vec3(0, 0, 0);
		scale = vec4(1, 1, 1, 0);
	}
};
