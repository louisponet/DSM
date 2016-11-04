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