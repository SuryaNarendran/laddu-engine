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


void WorldObject::Draw() {

	//send transform uniform to shader

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

