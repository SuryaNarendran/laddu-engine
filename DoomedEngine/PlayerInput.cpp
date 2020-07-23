#include "PlayerInput.h"

float PlayerInput::zAxis;
float PlayerInput::xAxis;
int PlayerInput::axisInputDelay;
float PlayerInput::pointerX;
float PlayerInput::pointerY;
float PlayerInput::pointerDeltaX;
float PlayerInput::pointerDeltaY;
float PlayerInput::angXCoveredSinceLastPtrInput;
float PlayerInput::angYCoveredSinceLastPtrInput;

const float PlayerInput::playerSpeed = 2.0f;
const float PlayerInput::mouseSpeed = 90.0f;
const int PlayerInput::axisInputReleaseTime = 80;
const int PlayerInput::mouseCatchDistance = 100;
const float PlayerInput::mouseSensitivity = 0.001f;


int PlayerInput::time;

void PlayerInput::Init() {
	zAxis = 0;
	xAxis = 0;
	axisInputDelay = 0;
	pointerX = WINDOW_WIDTH / 2.0f;
	pointerY = WINDOW_HEIGHT / 2.0f;
	pointerDeltaX = 0;
	pointerDeltaY = 0;
	time = glutGet(GLUT_ELAPSED_TIME);
	angXCoveredSinceLastPtrInput = 0;
	angYCoveredSinceLastPtrInput = 0;
}