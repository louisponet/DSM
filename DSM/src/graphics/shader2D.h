#pragma once
#include "shader.h"

class Shader2D :public Shader
{
public:
	Shader2D(const char* vertPath, const char* fragPath);
	~Shader2D();
	void setLightProperties(const Light& light);
};