#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "../graphics/GL.h"

class Renderable3D
{
protected:
	Renderable3D(glm::vec3 c, float spec_int,float spec_pow);
	Renderable3D(std::vector<glm::vec3> vertices,  std::vector<glm::vec3> normals,  std::vector<GLuint> indices,  glm::vec3 c,  float spec_int,  float spec_pow);


public:
	~Renderable3D();
	std::vector<glm::vec3>vertices,normals;
	std::vector<GLuint> indices;
	glm::vec3 colour;
	glm::mat4 mat;
	float specIntensity, specPower;


protected:

	virtual void initInfo();
};