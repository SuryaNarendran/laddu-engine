#pragma once

#include "DOOM.h"
#include "WorldObject.h"
#include "Transformable.h"
#include "Scene.h"
#include "GraphicsData.h"
#include "PlayerInput.h"
#include "SceneLoader.h"

class MainLoop {
public:

	static void init();

	static void reshape(int w, int h);

	static void display(void);

	static void kbhandle(unsigned char testchar, int mouseX, int mouseY);

	static void passiveMouse(int mouseX, int mouseY);

	static void update();

private:

	static Scene activeScene;
};