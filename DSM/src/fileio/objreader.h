#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "../graphics/GL.h"

class objReader
{
public:
	objReader();
	~objReader();

	bool loadOBJ(const char*path, std::vector<glm::vec3>&out_vertices, std::vector<GLuint>&out_indices,std::vector<glm::vec3>&out_normals);
};

