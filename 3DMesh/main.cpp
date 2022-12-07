#include "Camera.h"
#include "Utils.h"
#include "Mesh.h"

// Initialize camera
Camera camera;

std::vector<floatvec> vertices;
std::vector<floatvec> normals;
std::vector<std::vector<GLushort>> DinoOrder;

const int refreshMillis = 30;
const int speedTickMillis = 100;

struct vector2d {
	double x, y;
};

bool dragging = false;
const double ROTATEFACTOR = 500.0;

vector2d mouseSpeed = { 0, 0 };
vector2d mouseCurPos = { 0, 0 };
vector2d mousePrevPos = { 0, 0 };
vector2d cameraSpeed = { 0, 0 };

// call every speedTickMillis
const int momentum = 0.1;
void updateMousePos() {
	if (dragging) {
		mouseSpeed.x = mouseCurPos.x - mousePrevPos.x;
		mouseSpeed.y = mouseCurPos.y - mousePrevPos.y;
		mousePrevPos.x = mouseCurPos.x;
		mousePrevPos.y = mouseCurPos.y;
		cameraSpeed.x = mouseSpeed.x / ROTATEFACTOR;
		cameraSpeed.y = mouseSpeed.y / ROTATEFACTOR;
	}
	else {
		cameraSpeed.x *= 0.8;
		cameraSpeed.y *= 0.8;
	}
}

// Handles the keyboard event: the left and right arrows bend the elbow, the
// up and down keys bend the shoulder.
void special(int key, int, int) {
	switch (key) {
	case GLUT_KEY_LEFT: camera.moveLeft(); break;
	case GLUT_KEY_RIGHT: camera.moveRight(); break;
	case GLUT_KEY_UP: camera.incRadius(); break;
	case GLUT_KEY_DOWN: camera.decRadius(); break;
	}
	glutPostRedisplay();
}

// Handles the keyboard event: 
void key(unsigned char key, int, int) {
	switch (key) {
	}
	glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (dragging == false) {
			mousePrevPos.x = x;
			mousePrevPos.y = y;
			mouseCurPos.x = x;
			mouseCurPos.y = y;
			cameraSpeed.x = 0;
			cameraSpeed.y = 0;
		}
		dragging = true;
		
		printf("drag! %d, %d\n", x, y);
		glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		dragging = false;
		printf("release! %d, %d\n", x, y);
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	}
}

void mouseMove(int x, int y) {
	if (dragging == true) {
		mouseCurPos.x = x;
		mouseCurPos.y = y;
	}
}

void mouseWheel(int wheel, int direction, int x, int y)
{
	// Increment/decrement the global pointSize depending on the direction 
	// of rotation of the mouse wheel.
	(direction > 0) ? camera.decRadius() : camera.incRadius();

	glutPostRedisplay();
}

void display() {  

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	floatvec up = camera.getCameraUp();

	gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
		centerX, centerY, centerZ,
		up[0], up[1], up[2]);

	draw_obj(vertices, normals, DinoOrder);

	drawAxis();

	glutSwapBuffers();
}

// Handles the reshape event by setting the viewport so that it takes up the
// whole visible region, then sets the projection matrix to something reason-
// able that maintains proper aspect ratio.
void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.01, 6.0);
	glMatrixMode(GL_MODELVIEW);
}

/* Called back when the timer expired, used to rerender display */
void refreshDisplay(int value) {
	camera.rotate(-cameraSpeed.x, -cameraSpeed.y);
	glutPostRedisplay();    // Post a paint request to activate display()
	glutTimerFunc(refreshMillis, refreshDisplay, 0); // subsequent timer call at milliseconds
}

void speedTick(int value) {
	updateMousePos();
	glutTimerFunc(speedTickMillis, speedTick, 0); // subsequent timer call at milliseconds
}

void init() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	load_obj("dino.obj", vertices, normals, DinoOrder);

	// glPointLightSource
	GLfloat diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat ambient0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light0_pos[] = { 5.0, 5.0, 5.0, 1.0 };

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.01);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// does application initialization; enters the main event loop.
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3DMesh: DINO");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutSpecialFunc(special);
	glutMotionFunc(mouseMove);
	glutMouseFunc(mouseFunc);
	glutMouseWheelFunc(mouseWheel);
	glutTimerFunc(0, refreshDisplay, 0);   // Refresh rate
	glutTimerFunc(0, speedTick, 0);
	init();
	glutMainLoop();
}