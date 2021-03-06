
#include <vector>
#include <cmath>
#include "cone.h"
#include "../fileio/objreader.h"
#include "../utils/maths.h"



Cone::Cone(glm::vec3 v1, glm::vec3 v2, float radius, glm::vec3 colour, float specIntensity, float specPower)
	:Renderable3D(BaseCone::instance()->getVertices(), BaseCone::instance()->getNormals(), BaseCone::instance()->getIndices(), colour, specIntensity, specPower), v1(v1), v2(v2), radius(radius)

{
	genMat();
}



Cone::Cone() :Renderable3D(glm::vec3(0.0f), 0.0f, 0.0f), v1(glm::vec3(0.0f)), v2(glm::vec3(0.0f)), radius(1.0f)
{
	initInfo();
}

Cone::~Cone()
{

}

void Cone::genMat()
{

	glm::vec3 vr = v2 - v1;
	float l = glm::length(vr);
	float angle = acos(vr[2] / l);
	glm::vec3 rotAx = normalize(glm::cross(glm::vec3(0.0000000001f, 0.0f, 1.0f), vr));
	if (glm::length(rotAx) > 0.0001) {
		mat = maths::translateCM(maths::rotateCM(maths::scaleCM(glm::vec3(radius, radius, l)), angle, rotAx), v1);
	}
	else {
		mat = maths::translateCM(glm::mat4(), v1)*maths::scaleCM(glm::vec3(radius, radius, l));
	}
}

void Cone::initInfo()
{
	objReader reader;
	normals.reserve(128);
	indices.reserve(186);
	vertices.reserve(128);
	reader.loadOBJ("src/renderables/cone.obj", vertices, indices, normals);

}


BaseCone::BaseCone() :Cone()
{

}

BaseCone::~BaseCone()
{
	if (cone_instance)
	{
		delete cone_instance;
	}
}

std::vector<glm::vec3> BaseCone::getVertices()
{
	return vertices;
}
std::vector<glm::vec3> BaseCone::getNormals()
{
	return normals;
}
std::vector<GLuint> BaseCone::getIndices()
{
	return indices;
}