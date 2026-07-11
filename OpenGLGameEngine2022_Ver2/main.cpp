#include "Engine.h"
#include "SceneManager.h"
#include "TextureManager.h"

using namespace std;

int windowWidth = 700;
int windowHeight = 900;

chrono::system_clock::time_point lastFrameTime;

/*forward declaration of functions*/
void Update(int n);
void SpKeyboard(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void MouseClick(int button, int state, int x, int y);
void MouseMove(int x, int y);

void initRendering() {
	glEnable(GL_DEPTH_TEST);                    // test 3D depth
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void cameraSetup(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);                // select projection matrix
	glLoadIdentity();                           // reset projection matrix
	//gluPerspective(45.0, 1, 1.0, 200.0);      // 3D Camera
	gluOrtho2D(0, w, 0, h);						// 2D Camera
}

void display() {
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear Screen and Depth Buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	SceneManager::GetInstance()->Draw();

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	std::cout << "Programmer: Ko\n";
	std::cout << "Compiled on " << __DATE__ << ", " << __TIME__ << std::endl << std::endl;

	// init GLUT and create Window
	glutInit(&argc, argv);                      // GLUT initialization
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);               // set the window size

	// create the window
	glutCreateWindow("MAZMORRA");
	initRendering();                            // initialize rendering

	lastFrameTime = chrono::system_clock::now();
	srand(time(NULL));
	SceneManager::GetInstance()->LoadScene("TitleScene");

	// register handler functions
	glutReshapeFunc(cameraSetup);               // resiz window and camera setup
	glutDisplayFunc(display);                   // Display function
	glutKeyboardFunc(Keyboard);					// Keyboard handler
	glutSpecialFunc(SpKeyboard);
	glutMouseFunc(MouseClick);				// Mouse Click handler
	glutPassiveMotionFunc(MouseMove);			// Mouse move without mourse button pressed
	//glutMotionFunc(mouseOnClickMove);			// Mouse move with mourse button pressed
	//glutIdleFunc(idleUpdate);
	glutTimerFunc(30, Update, 0);				// Timer function

	glutMainLoop();                             // run GLUT mainloop
	return(0);                                  // this line is never reached
}

void Update(int n) {
	glutPostRedisplay();

	chrono::system_clock::time_point curFrameTime = chrono::system_clock::now();
	chrono::system_clock::duration deltaTime = curFrameTime - lastFrameTime;
	float dt = deltaTime.count() / 10000000.0f;
	SceneManager::GetInstance()->Update(dt);

	lastFrameTime = curFrameTime;
	glutTimerFunc(30, Update, 0);
}
void SpKeyboard(int key, int x, int y) {
	/* Translate GLUT_KEY to string you needed*/
}
void Keyboard(unsigned char key, int x, int y) {
	string tmp(1, key);
	SceneManager::GetInstance()->KeyDown(tmp);
}

void MouseClick(int button, int state, int x, int y) {
	/*
	*button : GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON
	*state : GLUT_UP or GLUT_DOWN
	*/
	if (state == GLUT_DOWN) {
		SceneManager::GetInstance()->MouseOnClick(button, state, x, windowHeight - y);
	}

}
void MouseMove(int x, int y) {
	SceneManager::GetInstance()->MouseMove(x, windowHeight - y);
}