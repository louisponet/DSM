#pragma once
#include "renderable3D.h"


class Cylinder : public Renderable3D
{
public:
	Cylinder();
	Cylinder(glm::vec3& v1, glm::vec3& v2, float radius, glm::vec3& colour, float specIntensity, float specPower);

	~Cylinder();

	void genMat();
private:
	glm::vec3 v1;
	glm::vec3 v2;
	float radius;
	void initInfo() override;

};