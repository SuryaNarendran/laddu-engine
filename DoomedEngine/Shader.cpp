#include "Shader.h"

Shader::Shader(GLuint _programID, GLuint _modelViewID, GLuint _projectionID, GLuint _transformID) {
	programID = _programID;
	modelViewID = _modelViewID;
	projectionID = _projectionID;
	transformID = _transformID;
}
Shader::Shader() {}