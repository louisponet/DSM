#include "global.h"

BaseSphere::BaseSphere():Sphere()
{

}

BaseSphere::~BaseSphere()
{
	if (sph_instance)
	{
		delete sph_instance;
	}
}

std::vector<glm::vec3> BaseSphere::getVertices()
{
	return vertices;
}
std::vector<glm::vec3> BaseSphere::getNormals()
{
	return normals;
}
std::vector<GLuint> BaseSphere::getIndices()
{
	return indices;
}



BaseCylinder::BaseCylinder():Cylinder()
{

}

BaseCylinder::~BaseCylinder()
{
	if (cyl_instance)
	{
		delete cyl_instance;
	}
}

std::vector<glm::vec3> BaseCylinder::getVertices()
{
	return vertices;
}
std::vector<glm::vec3> BaseCylinder::getNormals()
{
	return normals;
}
std::vector<GLuint> BaseCylinder::getIndices()
{
	return indices;
}


BaseCube::BaseCube() :Cube()
{

}

BaseCube::~BaseCube()
{
	if (cub_instance)
	{
		delete cub_instance;
	}
}

std::vector<glm::vec3> BaseCube::getVertices()
{
	return vertices;
}
std::vector<glm::vec3> BaseCube::getNormals()
{
	return normals;
}
std::vector<GLuint> BaseCube::getIndices()
{
	return indices;
}
