#pragma once
#include "DOOM.h"
#include "Shader.h"

class  Material {
public:

	glm::vec4 ambientProperties, diffuseProperties, specularProperties;
	Shader shader;

	Material(glm::vec4 _ambientProperties, glm::vec4 _diffuseProperties, glm::vec4 _specularProperties, const Shader &_shader);
	Material();
};
