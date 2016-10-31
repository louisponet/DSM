#pragma once
#include "renderable3D.h"
class Cone : public Renderable3D
{
public:
	Cone();
	Cone(glm::vec3 v1, glm::vec3 v2, float radius, glm::vec3 colour, float specIntensity, float specPower);

	~Cone();

	void genMat();
private:
	glm::vec3 v1;
	glm::vec3 v2;
	float radius;
	void initInfo() override;
};