#include "Material.h"
#include "GraphicsData.h"

Material::Material(glm::vec4 _ambientProperties, glm::vec4 _diffuseProperties, glm::vec4 _specularProperties, const Shader &_shader)
	: shader(_shader){
	ambientProperties = _ambientProperties;
	diffuseProperties = _diffuseProperties;
	specularProperties = _specularProperties;
}

Material::Material() : shader(GraphicsData::GetShader(SHADER_DEFAULT)){}

void Material::TintWithColor(glm::vec4 color) {
	ambientProperties = ambientProperties * color;
	diffuseProperties = diffuseProperties * color;
	specularProperties = specularProperties * color;
}