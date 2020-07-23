#pragma once
#include "DOOM.h"
#include "Transformable.h"

class LightSource {
	public:
		vec4 diffuse;
		vec4 specular;

		LightSource();
		LightSource(vec4 _diffuse, vec4 _specular);
};

class PointLight : public LightSource, Transformable {
public:

	PointLight();
	PointLight(vec4 _diffuse, vec4 _specular);

};