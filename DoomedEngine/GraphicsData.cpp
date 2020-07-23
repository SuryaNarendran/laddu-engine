#include "GraphicsData.h"



// Create a GLSL program object from vertex and fragment shader files
void GraphicsData::InitShaders(const char* vShaderFile, const char* fShaderFile){

	struct ShaderData {
		const char*  filename;
		GLenum       type;
		GLchar*      source;
	}  shaderData[2] = {
	{ vShaderFile, GL_VERTEX_SHADER, NULL },
	{ fShaderFile, GL_FRAGMENT_SHADER, NULL }
	};

	GLuint program = glCreateProgram();


	for (int i = 0; i < 2; ++i) {
		ShaderData& s = shaderData[i];
		s.source = FileHandler::readFileToString(s.filename);
		//s.source = readShaderSource( s.filename );
		if (shaderData[i].source == NULL) {
			std::cerr << "Failed to read " << s.filename << std::endl;
			exit(EXIT_FAILURE);
		}
		//std::cerr << s.source << std::endl;

		GLuint shader = glCreateShader(s.type);

		glShaderSource(shader, 1, (const GLchar**)&s.source, NULL);
		glCompileShader(shader);

		GLint  compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			std::cerr << s.filename << " failed to compile:" << std::endl;
			GLint  logSize;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetShaderInfoLog(shader, logSize, NULL, logMsg);
			std::cerr << logMsg << std::endl;
			delete[] logMsg;
			exit(EXIT_FAILURE);
		}

		delete[] s.source;

		glAttachShader(program, shader);
	}

	/* link  and error check */
	glLinkProgram(program);

	GLint  linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked) {
		std::cerr << "Shader program failed to link" << std::endl;
		GLint  logSize;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
		char* logMsg = new char[logSize];
		glGetProgramInfoLog(program, logSize, NULL, logMsg);
		std::cerr << logMsg << std::endl;
		delete[] logMsg;

		exit(EXIT_FAILURE);
	}

	shaders = new Shader[1];
	Shader defaultShader = Shader(program,
		glGetUniformLocation(program, "model_view"),
		glGetUniformLocation(program, "projection"));

	shaders[SHADER_DEFAULT] = defaultShader;
}

void GraphicsData::InitMaterials() {
	Material defaultMaterial(vec4(1.0f, 0.0f, 0.0f, 1.0f),
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		shaders[SHADER_DEFAULT]);

	materials = new Material[1];
	materials[MATERIAL_DEFAULT] = defaultMaterial;
}


void GraphicsData::LoadModels() {

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint* buffers = new GLuint[3];

	glGenBuffers(2, buffers);

	//Create and initialize a vertex position buffer object
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*CubeData::cubevertexCount*4, CubeData::cubevertices, GL_STATIC_DRAW);

	// Create and initialize a element buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_UNSIGNED_INT)*CubeData::cubeelementCount, CubeData::cubeelements, GL_STATIC_DRAW);

	// Create and initialize a normal buffer object
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*CubeData::cubevertexCount*4, CubeData::cubenormals, GL_STATIC_DRAW);

	// Initialize the normal position attribute from the vertex shader
	GLuint nor = glGetAttribLocation(shaders[SHADER_DEFAULT].programID, "vNormal");
	glEnableVertexAttribArray(nor);
	glVertexAttribPointer(nor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	// Initialize the vertex position attribute from the vertex shader
	GLuint loc = glGetAttribLocation(shaders[SHADER_DEFAULT].programID, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	models = new Model[1];
	models[MODEL_CUBE] = Model(vao, buffers, CubeData::cubeelementCount, materials[0]);
}

WorldObject GraphicsData::GetDefaultCube() {
	return ElemBuffPrimitive3D(models[MODEL_CUBE]);
}

Shader GraphicsData::GetShader(int index) {
	return shaders[index];
}

Material* GraphicsData::materials;
Shader* GraphicsData::shaders;
Model* GraphicsData::models;