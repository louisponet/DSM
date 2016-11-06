#pragma once
#include "shader.h"

class Shader3D :public Shader
{
private:
	GLuint m_SelectedIndexLoc, m_ColourLoc, m_AmbIntensityLoc, m_DiffIntensityLoc, m_posLoc;
	Light m_Light;
public:
	Shader3D(const char* vertPath, const char* fragPath);
	~Shader3D();
	void setLightProperties(const Light& light);
	void setSelectedIndex(const unsigned int& index);

	void setDiffuseLighting(float value);
	void setAmbientLighting(float value);
	void enableDiffuseLighting();
	void initLocations();
private:

};