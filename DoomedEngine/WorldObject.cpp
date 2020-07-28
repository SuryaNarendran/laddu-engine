#include "WorldObject.h"

Model::Model(GLuint _vao, GLuint* _vboa, GLsizei _elementCount, Material _material) {
	vao = _vao;
	vboa = _vboa;
	elementCount = _elementCount;
	material = _material;
}

Model::Model() {

}

//NOTE: how do you make a copy constructor for a base class -> subclass??
WorldObject::WorldObject(Model model) : Transformable() {
	vao = model.vao;
	vboa = model.vboa;
	elementCount = model.elementCount;
	material = model.material;
}

WorldObject::WorldObject() : Transformable() {

}


void WorldObject::Draw(const Scene& scene) {

	//send uniforms to shader
	glm::mat4 tMatrix = GetTransformMatrix();
	glUniformMatrix4fv(material.shader.transformID, 1, GL_FALSE, glm::value_ptr(tMatrix));

	glm::vec4 ambientProduct = scene.ambientLight * material.ambientProperties;
	glm::vec4 diffuseProduct = scene.lightSources[0].diffuse * material.diffuseProperties;
	glm::vec4 specularProduct = scene.lightSources[0].specular * material.specularProperties;

	glUniform4fv(material.shader.ambientProductID, 1, value_ptr(ambientProduct));
	glUniform4fv(material.shader.diffuseProductID, 1, value_ptr(diffuseProduct));
	glUniform4fv(material.shader.specularProductID, 1, value_ptr(specularProduct));

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void ElemBuffPrimitive3D::Draw(){

	//send transform uniform to shader

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0);
}

ElemBuffPrimitive3D::ElemBuffPrimitive3D(Model model) : WorldObject(model) {}

