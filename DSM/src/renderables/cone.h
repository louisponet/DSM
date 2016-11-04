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

class BaseCone : private Cone
{
	static BaseCone* cone_instance;
private:
	BaseCone();

public:
	~BaseCone();
	static BaseCone* instance()
	{
		if (!cone_instance)
			cone_instance = new BaseCone();
		return cone_instance;

	};

	std::vector<glm::vec3> getVertices();
	std::vector <glm::vec3> getNormals();
	std::vector<GLuint> getIndices();
};