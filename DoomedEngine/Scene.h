//holds references for the objects that make up the game world, and methods to load them from file. 
#pragma once

#include "DOOM.h"
#include "WorldObject.h"
#include "Transformable.h"
#include "FileHandler.h"
#include "LightSource.h"
#include "GraphicsData.h"


struct PerspectiveCamera : public Transformable{

	GLfloat fovy;
	GLfloat aspect;
	GLfloat zNear;
	GLfloat zFar;

public:

	glm::mat4 GetModelViewMatrix();
	glm::mat4 GetProjectionMatrix();
	PerspectiveCamera();
	PerspectiveCamera(GLfloat _fovy, GLfloat _aspect, GLfloat _zNear, GLfloat _zFar);
};

class Scene{
	
	public:
	
	WorldObject* worldObjects;
	GLint worldObjectCount;
	LightingEnvironment lighting;
	
	PerspectiveCamera mainCamera;
};



