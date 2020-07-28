#include "Shader.h"

Shader::Shader(GLuint _programID) {
	programID = _programID;
	modelViewID = glGetUniformLocation(programID, "model_view");
	projectionID = glGetUniformLocation(programID, "projection");
	transformID = glGetUniformLocation(programID, "transform");
	lightPositionID = glGetUniformLocation(programID, "lightPosition");
	ambientProductID = glGetUniformLocation(programID, "AmbientProduct");
	diffuseProductID = glGetUniformLocation(programID, "DiffuseProduct");
	specularProductID = glGetUniformLocation(programID, "SpecularProduct");
}
Shader::Shader() {}