#pragma once

#include "DOOM.h"

class PlayerInput {
public:

	static void Init();

	static float zAxis, xAxis;
	static int axisInputDelay;

	static float pointerX, pointerY, pointerDeltaX, pointerDeltaY;

	static int time;

	static float angXCoveredSinceLastPtrInput;
	static float angYCoveredSinceLastPtrInput;

	const static float playerSpeed;
	const static float mouseSpeed;
	const static int axisInputReleaseTime;
	const static int mouseCatchDistance;
	const static float mouseSensitivity;
};
