#pragma once
#include "DOOM.h"
#include "Shader.h"

class  Material {
public:

	vec4 ambientProperties, diffuseProperties, specularProperties;

	Shader shader;
};
