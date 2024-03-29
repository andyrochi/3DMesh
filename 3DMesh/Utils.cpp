#include "Utils.h"

void drawAxis() {
	GLfloat ambientX[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat ambientY[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat ambientZ[] = { 0.0, 0.0, 1.0, 1.0 };
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientX);
	glColor3f(1.0, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientY);
	glColor3f(0, 1.0, 0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientZ);
	glColor3f(0.0, 0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();

	glPopMatrix();
}

floatvec crossProduct(floatvec& a, floatvec& b) {
	if (a.size() < 3 || b.size() < 3) {
		std::cerr << "input vector does not have dim of 3" << std::endl;
		return floatvec(0);
	}
	GLfloat x = a[1] * b[2] - a[2] * b[1];
	GLfloat y = a[2] * b[0] - a[0] * b[2];
	GLfloat z = a[0] * b[1] - a[1] * b[0];
	floatvec res = { x, y, z };
	return res;
}

GLfloat dotProduct(floatvec& a, floatvec& b) {
	if (a.size() < 3 || b.size() < 3) {
		std::cerr << "input vector does not have dim of 3" << std::endl;
		return 0;
	}

	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}
void normalize(floatvec& vec) {
	if (vec.size() < 3) {
		std::cerr << "input vector does not have dim of 3" << std::endl;
		return;
	}
	GLfloat length2 = vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
	GLfloat length = sqrt(length2);
	for (auto& v : vec)
		v /= length;
}

floatvec normalizedGet(floatvec& vec) {
	if (vec.size() < 3) {
		std::cerr << "input vector does not have dim of 3" << std::endl;
		return std::vector<GLfloat>(0);
	}
	floatvec res = vec;
	GLfloat length2 = vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
	GLfloat length = sqrt(length2);
	for (auto& v : res)
		v /= length;
	return res;
}