#pragma once
#include "DOOM.h"
#include "Transformable.h"

class LightSource {
	public:
		glm::vec4 diffuse;
		glm::vec4 specular;

		LightSource();
		LightSource(glm::vec4 _diffuse, glm::vec4 _specular);
};

class PointLight : public LightSource, public Transformable {
public:

	PointLight();
	PointLight(glm::vec4 _diffuse, glm::vec4 _specular);

};

class LightingEnvironment {
public:

	PointLight* sources;
	GLint sourceCount;
	glm::vec4 ambient;
};