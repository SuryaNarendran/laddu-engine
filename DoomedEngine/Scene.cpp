//holds references for the objects that make up the game world, and methods to load them from file. 
#include "Scene.h"


void Scene::LoadNew(const char* filename) {

	//char* levelFileString = FileHandler::readFileToString(filename);

	mainCamera = PerspectiveCamera(45.0, (GLfloat)WINDOW_WIDTH / WINDOW_HEIGHT, 0.5f, 30.0f);

	mainCamera.position = vec4(0, 0, -5, 1);
	mainCamera.eulerAngles = vec3(0, 0, 0);

	lightSources = new PointLight();
	lightSourceCount = 1;

	ambientLight = vec4(0.50, 0.0, 0.0, 1.0);

	worldObjectCount = 1;
	worldObjects = new WorldObject[worldObjectCount];

	worldObjects[0] = GraphicsData::GetDefaultCube();
}

//Taken from mat.h -> Angel Interactive Computer Graphics
mat4 PerspectiveCamera::GetProjectionMatrix()
{
	/*GLfloat top = tan(fovy*DEG_TO_RAD / 2) * zNear;
	GLfloat right = top * aspect;

	mat4 c(1.0f);
	c[0][0] = zNear / right;
	c[1][1] = zNear / top;
	c[2][2] = -(zFar + zNear) / (zFar - zNear);
	c[2][3] = -2.0*zFar*zNear / (zFar - zNear);
	c[3][2] = -1.0;
	return c;*/

	return perspective(fovy, aspect, zNear, zFar);
}

//Taken from mat.h -> Angel Interactive Computer Graphics
mat4 PerspectiveCamera::GetModelViewMatrix()
{
	vec4 eye = position;
	vec4 forward = vec4(0, 0, 1,0);
	vec4 up(0, 1, 0, 0);

	mat4 rotationMatrix(1.0f);
	rotationMatrix = rotate(rotationMatrix, eulerAngles[2], vec3(0, 0, 1));
	rotationMatrix = rotate(rotationMatrix, eulerAngles[1], vec3(0, 1, 0));
	rotationMatrix = rotate(rotationMatrix, eulerAngles[0], vec3(1, 0, 0));

	forward = rotationMatrix*forward;
	up = rotationMatrix*up;

	vec3 eye3(eye.x, eye.y, eye.z);
	vec3 forward3(forward.x, forward.y, forward.z);
	vec3 up3(up.x, up.y, up.z);

	return lookAt(eye3, eye3 + forward3, up3);
}

PerspectiveCamera::PerspectiveCamera() : Transformable(){}

PerspectiveCamera::PerspectiveCamera(GLfloat _fovy, GLfloat _aspect, GLfloat _zNear, GLfloat _zFar) : Transformable() {
	fovy = _fovy;
	aspect = _aspect;
	zNear = _zNear;
	zFar = _zFar;
}