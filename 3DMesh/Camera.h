#define _USE_MATH_DEFINES
#include "Utils.h"
#include <cmath>
// A camera.  It moves horizontally in a circle centered at the origin of
// radius 10.  It moves vertically straight up and down.

const double TWO_PI = 2 * M_PI;

class Camera {
	double theta;      // determines the x and z positions
	double dTheta;     // increment in theta for swinging the camera around
	double phi;
	double dPhi;
	double radius;
	floatvec up;
public:
	Camera() : theta(0), dTheta(0.04), phi(M_PI / 2), dPhi(0.04), radius(2.0), up({0.0,0.0, 1.0}) {}
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

	void rotate(double dThetaP, double dPhiP, bool drag = false) {
		phi += dPhiP;
		theta += dThetaP;
	}

	floatvec getCameraUp() {
		floatvec posVec = { float(getX()), float(getY()), float(getZ()) };
		normalize(posVec);
		/*floatvec worldUp = { 0.0f, 0.0f, 1.0f };*/
		
		floatvec left = crossProduct(posVec, up);
		normalize(left);
		floatvec up = crossProduct(left, posVec);
		normalize(up);
		return up;
	}
};