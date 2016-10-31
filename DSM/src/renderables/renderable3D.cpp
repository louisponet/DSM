#include "renderable3D.h"

Renderable3D::Renderable3D(glm::vec3 c, float spec_int,float spec_pow): colour(c),specIntensity(spec_int),specPower(spec_pow)
{

}

Renderable3D::Renderable3D( std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals,  std::vector<GLuint> indices,  glm::vec3 c,  float spec_int,  float spec_pow) :
	vertices(vertices), normals(normals), indices(indices), colour(c), specIntensity(spec_int), specPower(spec_pow)
{

}

Renderable3D::~Renderable3D()
{

}



void Renderable3D::initInfo()
{

}