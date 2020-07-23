#include "LightSource.h"

LightSource::LightSource() {
	diffuse = vec4(0, 0, 0, 0);
	specular = vec4(0, 0, 0, 0);
};

LightSource::LightSource(vec4 _diffuse, vec4 _specular) {
	diffuse = _diffuse;
	specular = _specular;
}

PointLight::PointLight() : 
	Transformable(),
	LightSource() {}

PointLight::PointLight(vec4 _diffuse, vec4 _specular) :
	LightSource(diffuse, specular),
	Transformable() {}