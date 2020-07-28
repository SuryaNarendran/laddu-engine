#include "MainLoop.h"

void MainLoop::init() {

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutWarpPointer(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);

	// Load shaders and use the resulting shader program
	GraphicsData::InitShaders("std_vshader.glsl", "std_fshader.glsl");
	GraphicsData::InitMaterials();
	GraphicsData::LoadModels();

	//ideally this step would happen elsewhere
	Shader defaultShader = GraphicsData::GetShader(SHADER_DEFAULT);
	glUseProgram(defaultShader.programID);

	// Z-buffer based depth algorithm is enabled
	glEnable(GL_DEPTH_TEST);


	activeScene = SceneLoader::LoadNew("testLevel.doom");

	PlayerInput::Init();
}

void MainLoop::reshape(int w, int h){
		glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void MainLoop::display() {

	// clear the frame buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//setup uniform variables
	Shader defaultShader = GraphicsData::GetShader(SHADER_DEFAULT);

	glm::mat4 pMatrix = activeScene.mainCamera.GetProjectionMatrix();
	float* p = glm::value_ptr(pMatrix);
	glUniformMatrix4fv(defaultShader.projectionID, 1, GL_FALSE, p);

	glm::mat4 mvMatrix = activeScene.mainCamera.GetModelViewMatrix();
	float* mv = glm::value_ptr(mvMatrix);
	glUniformMatrix4fv(defaultShader.modelViewID, 1, GL_FALSE, mv);

	float* lp = glm::value_ptr(activeScene.lightSources[0].position);
	glUniform4fv(defaultShader.lightPositionID, 1, lp);

	//draw elements

	for (int i = 0;i < activeScene.worldObjectCount;i++) {
		WorldObject worldObject = activeScene.worldObjects[i];

		worldObject.Draw(activeScene);
	}

	glFlush();
}

void MainLoop::kbhandle(unsigned char inputchar, int mouseX, int mouseY) {

	switch (inputchar) {
	case 'w':
	case 'W':
		PlayerInput::zAxis = 1;
		break;
	case 's':
	case 'S':
		PlayerInput::zAxis = -1;
		break;
	default:
		PlayerInput::zAxis = 0;
	}
	switch (inputchar){
	case 'a':
	case 'A':
		PlayerInput::xAxis = 1;
		break;
	case 'd':
	case 'D':
		PlayerInput::xAxis = -1;
		break;
	default:
		PlayerInput::xAxis = 0;
	}

	PlayerInput::axisInputDelay = 0;
}

void MainLoop::passiveMouse(int mouseX, int mouseY) {

	PlayerInput::pointerDeltaX = mouseX - PlayerInput::pointerX;
	PlayerInput::pointerDeltaY = mouseY - PlayerInput::pointerY;

	if (mouseX >= WINDOW_WIDTH - PlayerInput::mouseCatchDistance || mouseX <= PlayerInput::mouseCatchDistance
		|| mouseY >= WINDOW_HEIGHT - PlayerInput::mouseCatchDistance || mouseY <= PlayerInput::mouseCatchDistance) {
		glutWarpPointer(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
		PlayerInput::pointerX = WINDOW_WIDTH / 2.0f;
		PlayerInput::pointerY = WINDOW_HEIGHT / 2.0f;
	}
	else {
		PlayerInput::pointerX = mouseX;
		PlayerInput::pointerY = mouseY;
	}
	PlayerInput::angXCoveredSinceLastPtrInput = 0;
	PlayerInput::angYCoveredSinceLastPtrInput = 0;
}

//split into functions that handle pointer input and kb input 
void MainLoop::update() {

	int newTime = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = newTime - PlayerInput::time;
	PlayerInput::time = newTime;

	if(abs(PlayerInput::pointerDeltaX) > FLOAT_EPSILON ||
		abs(PlayerInput::pointerDeltaY) > FLOAT_EPSILON){

		//negative because +x in screen coordinates corresponds to a clockwise rotation
		float deltaTheta = -PlayerInput::pointerDeltaX * PlayerInput::mouseSensitivity - PlayerInput::angYCoveredSinceLastPtrInput;
			float deltaPhi = PlayerInput::pointerDeltaY * PlayerInput::mouseSensitivity - PlayerInput::angXCoveredSinceLastPtrInput;
			float xAxisRot = std::fmin(deltaPhi, PlayerInput::mouseSpeed*deltaTime / 1000.0f);
			float yAxisRot = std::fmin(deltaTheta, PlayerInput::mouseSpeed*deltaTime / 1000.0f);
			activeScene.mainCamera.Rotate(xAxisRot, yAxisRot, 0);
			PlayerInput::angXCoveredSinceLastPtrInput += xAxisRot;
			PlayerInput::angYCoveredSinceLastPtrInput += yAxisRot;
	}
	if (abs(PlayerInput::xAxis) > FLOAT_EPSILON ||
		abs(PlayerInput::zAxis) > FLOAT_EPSILON) {

		float movementSpeed = PlayerInput::playerSpeed * deltaTime / 1000.0f;

		glm::mat4 playerRotation = glm::rotate(glm::mat4(1.0f),
			activeScene.mainCamera.eulerAngles.y,
			glm::vec3(0, 1, 0));
		glm::vec3 playerXAxis = playerRotation*glm::vec4(1,0,0,0);
		glm::vec3 playerZAxis = playerRotation*glm::vec4(0, 0, 1, 0);
		activeScene.mainCamera.Translate(
			PlayerInput::xAxis*movementSpeed*playerXAxis +
			PlayerInput::zAxis*movementSpeed*playerZAxis);
	}

	PlayerInput::axisInputDelay += deltaTime;
	if (PlayerInput::axisInputDelay > PlayerInput::axisInputReleaseTime) {
		PlayerInput::xAxis = 0;
		PlayerInput::zAxis = 0;
		PlayerInput::axisInputDelay = 0;
	}

	glutPostRedisplay();
}

Scene MainLoop::activeScene;
