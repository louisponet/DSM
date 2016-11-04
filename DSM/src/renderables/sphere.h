
#pragma once
#include "renderable3D.h"

class Sphere : public Renderable3D
{
public:
	Sphere();
	Sphere(glm::vec3 center, float radius, glm::vec3 colour, float specIntensity, float specPower, unsigned int index);

	~Sphere();
	void genMat();
		
private:

	void initInfo() override;
	void subdivide(int& depth);

public:
	float radius;
	glm::vec3 center;
	uint index;
};

class BaseSphere : private Sphere
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