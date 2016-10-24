#pragma once
#include "../graphics/GL.h"
#include <glm/glm.hpp>

struct Light {
	glm::vec3 colour,center,focus;
	float ambIntensity, diffIntensity;
};
