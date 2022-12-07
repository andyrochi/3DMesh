#pragma once
#define _USE_MATH_DEFINES
#include "Utils.h"
#include <cmath>

class Light {
	double theta;      // determines the x and z positions
	double phi;
	double radius;
	GLenum lightIndex;
	floatvec ambient;
	floatvec diffuse;
	floatvec specular;

public:
	Light() :theta(M_PI / 4), phi(M_PI / 4), radius(3.0), lightIndex(GL_LIGHT0)
		, diffuse({ 1.0, 1.0, 1.0, 1.0 }), ambient({ 1.0, 1.0, 1.0, 1.0 }), specular({ 1.0, 1.0, 1.0, 1.0 }) {}
	Light(GLenum index) :theta(M_PI / 4), phi(M_PI / 4), radius(3.0), lightIndex(index)
		, diffuse({ 1.0, 1.0, 1.0, 1.0 }), ambient({ 1.0, 1.0, 1.0, 1.0 }), specular({ 1.0, 1.0, 1.0, 1.0 }) {}

	double getX() { return radius * sin(phi) * cos(theta); }
	double getY() { return radius * sin(phi) * sin(theta); }
	double getZ() { return radius * cos(phi); }
	floatvec getPos() { return {float(getX()), float(getY()), float(getZ()), 1}; }
	
	void incRadius() {
		radius += 0.1;
		if (radius >= 5)
			radius = 5;
	}
	void decRadius() {
		radius -= 0.1;
		if (radius < 1)
			radius = 1;
	}

	void rotate(double dThetaP, double dPhiP) {
		phi += dPhiP;
		theta += dThetaP;
		glLightfv(lightIndex, GL_POSITION, getPos().data());
	}

	void setAmbient(floatvec amb) { ambient = amb; }
	void setDiffuse(floatvec dif) { diffuse = dif; }
	void setSpecular(floatvec spec) { specular = spec; }
	floatvec getAmbient() { return ambient; }
	floatvec getDiffuse() { return diffuse; }
	floatvec getSpecular() { return specular; }
	const GLfloat* getAmbientRaw() { return ambient.data(); }
	const GLfloat* getDiffuseRaw() { return diffuse.data(); }
	const GLfloat* getSpecularRaw() { return specular.data(); }

};