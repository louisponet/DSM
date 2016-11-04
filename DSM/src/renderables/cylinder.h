#pragma once
#include "renderable3D.h"

class Cylinder : public Renderable3D
{
public:
	enum CylinderType {
		STRUCTURE,
		NORMAL
	};
	Cylinder();
	Cylinder(glm::vec3 v1, glm::vec3 v2, float radius, glm::vec3 colour, float specIntensity, float specPower,CylinderType type);

	~Cylinder();

	void genMat();
private:

	glm::vec3 v1;
	glm::vec3 v2;
	float radius;
	CylinderType type;
	void initInfo() override;

};

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