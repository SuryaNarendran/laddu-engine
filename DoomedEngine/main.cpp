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
		cout << "glewInit failed, aborting." << endl;
		exit(1);
	}
	cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << endl;
	cout << "OpenGL version " << glGetString(GL_VERSION) << " supported" << endl;
	cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << endl;

	MainLoop::init();
	glutDisplayFunc(MainLoop::display);
	glutReshapeFunc(MainLoop::reshape);

	glutMainLoop();
	return 0;
}
