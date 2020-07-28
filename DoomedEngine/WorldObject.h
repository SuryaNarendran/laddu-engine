//a class for objects that can be drawn in the game world
#pragma once
#include "DOOM.h"
#include "Transformable.h"
#include "Material.h"
#include "Scene.h"

//NOTE: change to const & arguments

class Model{
	
	public:
		GLuint vao;
		GLuint* vboa;
		GLsizei elementCount;
		Material material;
		const char* name;
		
	public:
		Model(GLuint _vao, GLuint* _vboa, GLsizei _elementCount, Material _material);
		Model();
};

class WorldObject : public Model, public Transformable {

public:
	WorldObject();
	WorldObject(Model model);
	virtual void Draw(const Scene& scene);

};

//class Primitive3D : public WorldObject{
//	
//	public:
//		Primitive3D(Model model);
//		vec4 color;
//				
//	public:	
//		void Draw();
//};

class ElemBuffPrimitive3D : public WorldObject {

public:
	ElemBuffPrimitive3D(Model model);
	glm::vec4 color;

public:
	void Draw() override;
};
