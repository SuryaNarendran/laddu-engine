#include "LightSource.h"

LightSource::LightSource() {
	diffuse = glm::vec4(0, 0, 0, 0);
	specular = glm::vec4(0, 0, 0, 0);
};

LightSource::LightSource(glm::vec4 _diffuse, glm::vec4 _specular) {
	diffuse = _diffuse;
	specular = _specular;
}

PointLight::PointLight() : 
	Transformable(),
	LightSource() {}

PointLight::PointLight(glm::vec4 _diffuse, glm::vec4 _specular) :
	LightSource(diffuse, specular),
	Transformable() {}