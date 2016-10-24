
#pragma once
#include "renderable3D.h"

class Sphere : public Renderable3D
{
public:
	Sphere();
	Sphere(glm::vec3 &center, float radius, glm::vec3 colour, float specIntensity, float specPower, unsigned int index);

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