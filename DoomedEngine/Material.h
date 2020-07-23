#pragma once
#include "DOOM.h"
#include "Shader.h"

class  Material {
public:

	vec4 ambientProperties, diffuseProperties, specularProperties;
	Shader shader;

	Material(vec4 _ambientProperties, vec4 _diffuseProperties, vec4 _specularProperties, const Shader &_shader);
	Material();
};
