#pragma once
#include "DOOM.h"
#include "Transformable.h"

class LightSource {
	public:
		vec4 diffuse;
		vec4 specular;
};

class PointLight : public LightSource, Transformable {
public:

};