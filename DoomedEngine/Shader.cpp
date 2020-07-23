#include "Shader.h"

Shader::Shader(GLuint _programID, GLuint _modelViewID, GLuint _projectionID) {
	programID = _programID;
	modelViewID = _modelViewID;
	projectionID = _projectionID;
}
Shader::Shader() {}