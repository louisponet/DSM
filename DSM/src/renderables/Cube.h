#pragma once

#include "renderable3D.h"

class Cube:public Renderable3D
{
public:
	Cube(glm::vec3  vector1, glm::vec3  vector2, float width, glm::vec3 colour);

	Cube();
	~Cube();

	void genMat( );

private:
	glm::vec3 v1;
	glm::vec3 v2;
	float width;
	void initInfo() override;
};