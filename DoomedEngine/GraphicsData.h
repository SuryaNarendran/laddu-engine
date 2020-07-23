#pragma once

#include "DOOM.h"
#include "FileHandler.h"
#include "WorldObject.h"
#include "Material.h"
#include "Shader.h"
#include "CubeData.h"

#define SHADER_DEFAULT 0

#define MATERIAL_DEFAULT 0

#define MODEL_CUBE 0


class GraphicsData {

public:


	// Create a GLSL program object from vertex and fragment shader files
	static void InitShaders(const char* vertexShaderFile,
		const char* fragmentShaderFile);

	static void InitMaterials();

	static void LoadModels();

	static WorldObject GetDefaultCube();

	static Shader GetShader(int index);

	static Material GetMaterial(int index);

private:

	static Shader* shaders;

	static Model* models;

	static Material* materials;
};