#pragma once

#include "DOOM.h"
#include "WorldObject.h"
#include "Transformable.h"
#include "Scene.h"
#include "GraphicsData.h"

class MainLoop {
public:

	static void init();

	static void reshape(int w, int h);

	static void display(void);

private:

	static Scene activeScene;
};