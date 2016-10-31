#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif
#include <vector>
#include <cmath>

#include "../global.h"
#include "cylinder.h"
#include "../fileio/objreader.h"
#include "../utils/maths.h"

Cylinder::Cylinder(glm::vec3 v1, glm::vec3 v2, float radius, glm::vec3 colour, float specIntensity, float specPower)
	:Renderable3D(BaseCylinder::instance()->getVertices(), BaseCylinder::instance()->getNormals(), BaseCylinder::instance()->getIndices(), colour, specIntensity,specPower), v1(v1), v2(v2), radius(radius)

{
	genMat();
}



Cylinder::Cylinder() :Renderable3D(glm::vec3(0.0f), 0.0f, 0.0f), v1(glm::vec3(0.0f)), v2(glm::vec3(0.0f)), radius(1.0f)
{
	initInfo();
}

Cylinder::~Cylinder()
{

}

void Cylinder::genMat()
{
	
	glm::vec3 vr = v2 - v1;
	float l = glm::length(vr);
	float angle = acos(vr[2] / l);
    glm::vec3 rotAx = normalize(glm::cross(glm::vec3(0.0000000001f, 0.0f, 1.0f), vr));
	if (glm::length(rotAx) > 0.0001) {
        mat = maths::translateCM(maths::rotateCM(maths::scaleCM(glm::vec3(radius, radius, l)), angle, rotAx),v1);
	}
	else {
        mat = maths::translateCM(glm::mat4(), v1)*maths::scaleCM(glm::vec3(radius, radius, l));
	}
}

void Cylinder::initInfo()
{
	objReader reader;
	normals.reserve(64);
	indices.reserve(372);
	vertices.reserve(64);
    reader.loadOBJ("src/renderables/cylinder.txt", vertices, indices, normals);
 
}
