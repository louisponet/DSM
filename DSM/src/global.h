#pragma once


#include "renderables/sphere.h"
#include "renderables/cylinder.h"
#include "renderables/Cube.h"

//----------------------BaseSphere-----------------------//

class BaseSphere: private Sphere
{
	static BaseSphere* sph_instance;
private:
	BaseSphere();

public:
	~BaseSphere();
	static BaseSphere* instance()
	{
		if (!sph_instance)
			sph_instance = new BaseSphere();
		return sph_instance;

	};

	std::vector<glm::vec3> getVertices();
	std::vector <glm::vec3> getNormals();
	std::vector<GLuint> getIndices();
};

//----------------------BaseCylinder-----------------------//

class BaseCylinder : private Cylinder
{
	static BaseCylinder* cyl_instance;
private:
	BaseCylinder();

public:
	~BaseCylinder();
	static BaseCylinder* instance()
	{
		if (!cyl_instance)
			cyl_instance = new BaseCylinder();
		return cyl_instance;

	};

	std::vector<glm::vec3> getVertices();
	std::vector <glm::vec3> getNormals();
	std::vector<GLuint> getIndices();
};

//----------------------BaseCube-----------------------//

class BaseCube : private Cube
{
	static BaseCube* cub_instance;
private:
	BaseCube();

public:
	~BaseCube();
	static BaseCube* instance()
	{
		if (!cub_instance)
			cub_instance = new BaseCube();
		return cub_instance;

	};

	std::vector<glm::vec3> getVertices();
	std::vector <glm::vec3> getNormals();
	std::vector<GLuint> getIndices();
};

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}