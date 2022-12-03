// This program is from the OpenGL Programming Guide.  It shows a robot arm
// that you can rotate by pressing the arrow keys.
#include "Camera.h"
#include "Utils.h"

// Initialize camera
Camera camera;

std::vector<floatvec> vertices;
std::vector<floatvec> normals;
std::vector<std::vector<GLushort>> DinoOrder;

void load_obj(const char* filename, std::vector<floatvec>& vertices, std::vector<floatvec>& normals, std::vector<std::vector<GLushort>>& elements);
void draw_obj(std::vector<floatvec>& vertices, std::vector<floatvec>& normals, std::vector<std::vector<GLushort>>& elements);

// Handles the keyboard event: the left and right arrows bend the elbow, the
// up and down keys bend the shoulder.
void special(int key, int, int) {
	switch (key) {
	case GLUT_KEY_LEFT: camera.moveLeft(); break;
	case GLUT_KEY_RIGHT: camera.moveRight(); break;
	case GLUT_KEY_UP: camera.moveUp(); break;
	case GLUT_KEY_DOWN: camera.moveDown(); break;
	}
	glutPostRedisplay();
}

// Handles the keyboard event: 
void key(unsigned char key, int, int) {
	switch (key) {
	}
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

	//drawAxis();

	glutSwapBuffers();
}

// Handles the reshape event by setting the viewport so that it takes up the
// whole visible region, then sets the projection matrix to something reason-
// able that maintains proper aspect ratio.
void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.01, 5.0);
	glMatrixMode(GL_MODELVIEW);
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
	init();
	glutMainLoop();
}

void load_obj(const char* filename, std::vector<floatvec>& vertices, std::vector<floatvec>& normals, std::vector<std::vector<GLushort>>& elements)
{
	std::ifstream in(filename, std::ios::in);
	if (!in)
	{
		std::cerr << "Cannot open " << filename << std::endl;
		exit(1);
	}

	std::string line;
	GLfloat maxX = 0, maxY = 0, maxZ = 0;
	GLfloat minX = 0, minY = 0, minZ = 0;
	while (std::getline(in, line))
	{

		if (line.substr(0, 2) == "v ")
		{
			std::istringstream s(line.substr(2));
			std::vector<GLfloat> v(3);
			// x y z w
			s >> v[0]; s >> v[1]; s >> v[2];
			vertices.push_back(v);
			maxX = std::max(maxX, v[0]);
			minX = std::min(minX, v[0]);
			maxY = std::max(maxY, v[1]);
			minY = std::min(minY, v[1]);
			maxZ = std::max(maxZ, v[2]);
			minZ = std::min(minZ, v[2]);
		}
		else if (line.substr(0, 2) == "f ")
		{
			std::istringstream s(line.substr(2));
			GLushort a, b, c;
			s >> a; s >> b; s >> c;
			a--; b--; c--;
			std::vector<GLushort> t;

			t.push_back(a); t.push_back(b); t.push_back(c);
			elements.push_back(t);

			// compute normal
			floatvec vec1 = { vertices[b][0] - vertices[a][0], vertices[b][1] - vertices[a][1] , vertices[b][2] - vertices[a][2] };
			floatvec vec2 = { vertices[c][0] - vertices[a][0], vertices[c][1] - vertices[c][1] , vertices[c][2] - vertices[a][2] };

			floatvec normal = crossProduct(vec1, vec2);
			normalize(normal);

			normals.push_back(normal);
		}
		/* anything else is ignored */

	}
	
	GLfloat xOffset = -(maxX + minX) / 2;
	GLfloat yOffset = -(maxY + minY) / 2;
	GLfloat zOffset = -(maxZ + minZ) / 2;
	GLfloat xLen = (maxX - minX) / 2;
	GLfloat yLen = (maxY - minY) / 2;
	GLfloat zLen = (maxZ - minZ) / 2;
	GLfloat scale = std::max(xLen, yLen);
	scale = std::max(scale, zLen);
	// normalize
	for (auto& vertex : vertices) {
		// translate
		vertex[0] += xOffset;
		vertex[1] += yOffset;
		vertex[2] += zOffset;
		
		// scale
		vertex[0] /= scale;
		vertex[1] /= scale;
		vertex[2] /= scale;
	}
}

void draw_obj(std::vector<floatvec>& vertices, std::vector<floatvec>& normals, std::vector<std::vector<GLushort>>& triangles) {
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.8, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shine = 100.0;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);

	for (int i = 0; i < triangles.size(); i++) {
		GLushort v1 = triangles[i][0], v2 = triangles[i][1], v3 = triangles[i][2];
		glNormal3fv(normals[i].data());
		glBegin(GL_TRIANGLES);
			glVertex3fv(vertices[v1].data());
			glVertex3fv(vertices[v2].data());
			glVertex3fv(vertices[v3].data());
		glEnd();
	}
}