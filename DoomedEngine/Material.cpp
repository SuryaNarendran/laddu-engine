#include "Material.h"
#include "GraphicsData.h"

Material::Material(vec4 _ambientProperties, vec4 _diffuseProperties, vec4 _specularProperties, const Shader &_shader)
	: shader(_shader){
	ambientProperties = _ambientProperties;
	diffuseProperties = _diffuseProperties;
	specularProperties = _specularProperties;
}

Material::Material() : shader(GraphicsData::GetShader(SHADER_DEFAULT)){}