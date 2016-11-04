#include "shader3D.h"


Shader3D::Shader3D(const char* vertPath, const char* fragPath) :Shader(vertPath, fragPath)
{

}

Shader3D::~Shader3D()
{

}

void Shader3D::initLocations() {
	
	m_SelectedIndexLoc = glGetUniformLocation(m_ShaderID, "selected_index");
	m_ColourLoc = glGetUniformLocation(m_ShaderID, "gpoint_light.colour");
	m_AmbIntensityLoc = glGetUniformLocation(m_ShaderID, "gpoint_light.amb_intensity");
	m_DiffIntensityLoc = glGetUniformLocation(m_ShaderID, "gpoint_light.diff_intensity");
	m_posLoc = glGetUniformLocation(m_ShaderID, "gpoint_light.position");

}

void Shader3D::setSelectedIndex(const unsigned int& index) {

	glUniform1f(m_SelectedIndexLoc, (GLfloat)index);

}

void Shader3D::setLightProperties(const Light& light) {
	m_Light = light;

	glUniform3f(m_ColourLoc, light.colour.x, light.colour.y, light.colour.z);
	glUniform1f(m_AmbIntensityLoc, light.ambIntensity);
	glUniform1f(m_DiffIntensityLoc, light.diffIntensity);
	glUniform3f(m_posLoc, light.center.x, light.center.y, light.center.z);

}

void Shader3D::disableDiffuseLighting() {

	glUniform1f(m_DiffIntensityLoc, 0.0f);
	glUniform1f(m_AmbIntensityLoc, 0.4f);

}

void Shader3D::enableDiffuseLighting() {

	glUniform1f(m_DiffIntensityLoc, m_Light.diffIntensity);
	glUniform1f(m_AmbIntensityLoc, m_Light.ambIntensity);

}