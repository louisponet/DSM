
#include <cmath>
#include "../global.h"
#include "Cube.h"
#include "../fileio/objreader.h"
#include "../utils/maths.h"

Cube::Cube(glm::vec3  vector1, glm::vec3  vector2, float width, glm::vec3 colour1):
	Renderable3D(BaseCube::instance()->getVertices(), BaseCube::instance()->getNormals(), BaseCube::instance()->getIndices(), colour1, 0.9f, 10.0f),v1(vector1),v2(vector2),width(width)
{
	genMat();
}

Cube::Cube():Renderable3D(glm::vec3(1.0f), 0.0001f, 10.0f)
{
	initInfo();
}

Cube::~Cube()
{
}


void Cube::genMat()
{

	glm::vec3 vr = v2 - v1;
	float l = glm::length(vr);
	float angle = acos(vr[2] / l) + 0.00000001;
	glm::vec3 rotAx = glm::normalize(glm::cross(glm::vec3(0.0f, 0.0f, 1.0f),vr));
	if (glm::length(rotAx) > 0.0001) {
		mat = maths::translateCM(maths::rotateCM(maths::scaleCM( glm::vec3(width, width, l)), angle, rotAx), v1);
	}
	else {
		mat = maths::translateCM(maths::scaleCM( glm::vec3(width, width, l)), v1);
	}
}

void Cube::initInfo()
{
	objReader reader;
	vertices.reserve(8);
	normals.reserve(8);
	indices.reserve(36);
    reader.loadOBJ("src/renderables/cube.txt", vertices, indices, normals);

}
