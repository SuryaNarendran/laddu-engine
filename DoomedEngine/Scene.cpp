//holds references for the objects that make up the game world, and methods to load them from file. 
#include "Scene.h"

//Taken from mat.h -> Angel Interactive Computer Graphics
glm::mat4 PerspectiveCamera::GetProjectionMatrix()
{
	/*GLfloat top = tan(fovy*DEG_TO_RAD / 2) * zNear;
	GLfloat right = top * aspect;

	glm::mat4 c(1.0f);
	c[0][0] = zNear / right;
	c[1][1] = zNear / top;
	c[2][2] = -(zFar + zNear) / (zFar - zNear);
	c[2][3] = -2.0*zFar*zNear / (zFar - zNear);
	c[3][2] = -1.0;
	return c;*/

	return glm::perspective(fovy, aspect, zNear, zFar);
}

//Taken from mat.h -> Angel Interactive Computer Graphics
glm::mat4 PerspectiveCamera::GetModelViewMatrix()
{
	glm::vec4 eye = position;
	glm::vec4 forward = glm::vec4(0, 0, 1,0);
	glm::vec4 up(0, 1, 0, 0);

	glm::mat4 rotationMatrix(1.0f);
	rotationMatrix = rotate(rotationMatrix, eulerAngles[2], glm::vec3(0, 0, 1));
	rotationMatrix = rotate(rotationMatrix, eulerAngles[1], glm::vec3(0, 1, 0));
	rotationMatrix = rotate(rotationMatrix, eulerAngles[0], glm::vec3(1, 0, 0));

	forward = rotationMatrix*forward;
	up = rotationMatrix*up;

	glm::vec3 eye3(eye.x, eye.y, eye.z);
	glm::vec3 forward3(forward.x, forward.y, forward.z);
	glm::vec3 up3(up.x, up.y, up.z);

	return glm::lookAt(eye3, eye3 + forward3, up3);
}

PerspectiveCamera::PerspectiveCamera() : Transformable(){}

PerspectiveCamera::PerspectiveCamera(GLfloat _fovy, GLfloat _aspect, GLfloat _zNear, GLfloat _zFar) : Transformable() {
	fovy = _fovy;
	aspect = _aspect;
	zNear = _zNear;
	zFar = _zFar;
}