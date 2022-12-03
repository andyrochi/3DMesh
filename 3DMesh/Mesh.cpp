#include "Mesh.h"

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