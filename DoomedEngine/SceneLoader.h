#pragma once

#include "DOOM.h"
#include "Scene.h"
#include "FileHandler.h"
#include "GraphicsData.h"


struct ModelTemplate {
public:
	char* name;
	char* filename;
};

struct WorldObjectTemplate {
public:
	char* name;
	char* model;
	glm::vec3 position;
	glm::vec3 eulerAngles;
	glm::vec3 scale;
};

class SceneLoader {
public:

	static Scene LoadNew(const char* filename);

private:

	static void CopyStringData(char** destination, char** source) {
		*destination = new char[strlen(*source)+1];
		strcpy_s(*destination, strlen(*source) + 1, *source);
	}

};