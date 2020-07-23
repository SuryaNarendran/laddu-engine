//Modern OpenGL version of Pseudo-Doom Engine
//Author: Surya Narendran
//05-06-2020

#include "DOOM.h"
#include "MainLoop.h"


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	//glutInitWindowPosition(200, 200);
	glutCreateWindow("DOOM");

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cout << "glewInit failed, aborting." << std::endl;
		exit(1);
	}
	std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << "OpenGL version " << glGetString(GL_VERSION) << " supported" << std::endl;
	std::cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << std::endl;

	MainLoop::init();
	glutDisplayFunc(MainLoop::display);
	glutReshapeFunc(MainLoop::reshape);

	glutMainLoop();
	return 0;
}
