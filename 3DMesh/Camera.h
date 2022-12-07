#define _USE_MATH_DEFINES
#include "Utils.h"
#include <cmath>
// A camera.  It moves horizontally in a circle centered at the origin of
// radius 10.  It moves vertically straight up and down.

const double TWO_PI = 2 * M_PI;
bool set = false;
class Camera {
	double theta;      // determines the x and z positions
	double dTheta;     // increment in theta for swinging the camera around
	double phi;
	double dPhi;
	double radius;
	floatvec up;
	int invertTheta;
public:
	Camera() : theta(0), dTheta(0.04), phi(M_PI / 2), dPhi(0.04), radius(2.0), up({0.0,0.0, 1.0}), invertTheta(1) {}
	double getX() { return radius * sin(phi) * cos(theta); }
	double getY() { return radius * sin(phi) * sin(theta); }
	double getZ() { return radius * cos(phi); }
	void moveRight() {
		theta += this->dTheta;
		if (theta >= TWO_PI) 
			theta = 0;
	}
	void moveLeft() { theta -= this->dTheta; if (theta <= 0) theta = TWO_PI - this->dTheta; }
	void moveUp() { phi -= this->dPhi; if (phi <= 0.001) phi = 0.001; }
	void moveDown() { phi += this->dPhi; if (phi >= M_PI) phi = M_PI; }
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

	void rotate(double dThetaP, double dPhiP, bool drag = false) {
		phi += dPhiP;
		if (phi >= TWO_PI) phi -= TWO_PI;
		if (phi < -TWO_PI) phi += TWO_PI;
		theta += dThetaP * invertTheta;

		// some hacks to fix gimbal lock
		if (phi < 0 && !set) {
			up[2] = -1;
			set = true;
				invertTheta = -1;
		}
		if (phi > 0 && phi < M_PI && set) {
			up[2] = 1;
			set = false;
				invertTheta = 1;
		}
		if (phi > M_PI && !set) {
			up[2] = -1;
			set = true;
				invertTheta = -1;
		}
		if (phi < M_PI && phi > 0 && set) {
			up[2] = 1;
			set = false;
				invertTheta = 1;
		}
		if (phi < -M_PI && set) {
			up[2] = 1;
			set = false;
				invertTheta = 1;
		}
	}

	floatvec getCameraUp() {
		floatvec posVec = { float(getX()), float(getY()), float(getZ()) };
		
		normalize(posVec);
		
		/*floatvec worldUp = { 0.0f, 0.0f, 1.0f };*/
		
		floatvec left = crossProduct(posVec, up);
		normalize(left);
		floatvec up2 = crossProduct(left, posVec);
		normalize(up2);
		
		return up2;
	}
};