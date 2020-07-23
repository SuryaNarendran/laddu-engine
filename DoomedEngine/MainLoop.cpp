#include "MainLoop.h"

void MainLoop::init() {

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glutSetCursor(GLUT_CURSOR_NONE);

	// Load shaders and use the resulting shader program
	GraphicsData::InitShaders("std_vshader.glsl", "std_fshader.glsl");
	GraphicsData::InitMaterials();
	GraphicsData::LoadModels();

	//ideally this step would happen elsewhere
	Shader defaultShader = GraphicsData::GetShader(SHADER_DEFAULT);
	glUseProgram(defaultShader.programID);

	// Z-buffer based depth algorithm is enabled
	glEnable(GL_DEPTH_TEST);

	activeScene = Scene();
	activeScene.LoadNew("someNonsense.doom");
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

	//draw elements

	for (int i = 0;i < activeScene.worldObjectCount;i++) {
		WorldObject worldObject = activeScene.worldObjects[i];

		worldObject.Draw();
	}

	glFlush();
}

void MainLoop::kbhandle(unsigned char inputchar, int mouseX, int mouseY) {

	int xDelta = 0, zDelta = 0;

	switch (inputchar) {
	case 'w':
	case 'W':
		zDelta = 1;
		break;
	case 's':
	case 'S':
		zDelta = -1;
		break;
	}
	switch (inputchar){
	case 'a':
	case 'A':
		xDelta = 1;
		break;
	case 'd':
	case 'D':
		xDelta = -1;
		break;
	}

	float speed = PLAYER_SPEED / FRAMERATE;
	activeScene.mainCamera.Translate(xDelta*speed, 0, zDelta*speed);
	glutPostRedisplay();
}

Scene MainLoop::activeScene;
