#include <math.h>
#include "../global.h"
#include "sphere.h"
#include "../utils/maths.h"

Sphere::Sphere(glm::vec3 center, float radius, glm::vec3 colour, float specIntensity, float specPower, unsigned int Index) :
	Renderable3D(BaseSphere::instance()->getVertices(), BaseSphere::instance()->getNormals(), BaseSphere::instance()->getIndices(), colour, specIntensity, specPower),center(center),radius(radius),index(Index)
{

	genMat();
}

Sphere::Sphere():Renderable3D(glm::vec3(0.0f), 0.0f, 0.0f),center(glm::vec3(0.0f)), radius(1.0f)
{
	initInfo();
}

void Sphere::initInfo()
{
	using glm::mat4;
	using glm::vec3;
	float X = .525731112119133606;
	float Z = .850650808352039932;
	vertices = {
		vec3(-X,0,Z),vec3(X,0,Z),vec3(-X,0,-Z),vec3(X,0,-Z),
		vec3(0,Z,X),vec3(0,Z,-X),vec3(0,-Z,X),vec3(0,-Z,-X),
		vec3(Z,X,0),vec3(-Z,X,0),vec3(Z,-X,0),vec3(-Z,-X,0)
	};

	indices = {
		1,4 ,0,4,9,0 , 4,5,9,8,5,4 , 1,8,4,
		1,10,8,10,3,8,8,3,5 ,3,2,5 , 3,7,2,
		3,10,7,10,6,7,6,11,7,6,0,11, 6,1,0,
		10,1,6,11,0,9,2,11,9,5,2,9,11,2,7
	};
	int depth = 3;
	subdivide(depth);
	normals.reserve(4 * 120 * depth);
	normals = vertices;
}

void Sphere::genMat()
{
	using glm::mat4;
	using glm::vec3;

	mat = maths::translateCM(maths::scaleCM(vec3(radius, radius, radius)),center);
}

void Sphere::subdivide(int& depth)
{

	std::vector<GLuint> newIndices;
	std::vector<glm::vec3> newVertices;
	newVertices.reserve(4 * 120 * depth);
	newIndices.reserve(4 * 120 * 2 * depth);
	if (depth>0)
	{
		GLuint i1, i2, i3;
		glm::vec3 v1, v2, v3,v4,v5,v6;
		for (unsigned int i =0 ; i<indices.size();i+=3)
		{
			i1 = indices[i];
			i2 = indices[i+1];
			i3 = indices[i+2];
			v1 = vertices[i1];
			v2 = vertices[i2];
			v3 = vertices[i3];

			v4 = glm::normalize((v1 + v2) / 2.0f);
			v5 = glm::normalize((v2 + v3) / 2.0f);
			v6 = glm::normalize((v1 + v3) / 2.0f);

			newIndices.push_back(newVertices.size());
			newIndices.push_back(newVertices.size() + 3);
			newIndices.push_back(newVertices.size() + 5);
			newIndices.push_back(newVertices.size() + 3);
			newIndices.push_back(newVertices.size() + 1);
			newIndices.push_back(newVertices.size() + 4);
			newIndices.push_back(newVertices.size() + 4);
			newIndices.push_back(newVertices.size() + 2);
			newIndices.push_back(newVertices.size() + 5);
			newIndices.push_back(newVertices.size() + 3);
			newIndices.push_back(newVertices.size() + 4);
			newIndices.push_back(newVertices.size() + 5);
			newVertices.push_back(v1);
			newVertices.push_back(v2);
			newVertices.push_back(v3);
			newVertices.push_back(v4);
			newVertices.push_back(v5);
			newVertices.push_back(v6);
		}
		vertices = newVertices;
		indices = newIndices;
		depth -= 1;
		subdivide(depth);
	}
	
}

Sphere::~Sphere()
{

}