#include "shader2D.h"

Shader2D::Shader2D(const char* vertPath, const char* fragPath) :Shader(vertPath, fragPath)
{

}

Shader2D::~Shader2D()
{

}

void Shader2D::setLightProperties(const Light& light) {

	GLuint m_ColourLoc = glGetUniformLocation(m_ShaderID, "gpoint_light.colour");
	GLuint m_AmbIntensityLoc = glGetUniformLocation(m_ShaderID, "gpoint_light.amb_intensity");
	GLuint m_DiffIntensityLoc = glGetUniformLocation(m_ShaderID, "gpoint_light.diff_intensity");
	GLuint m_posLoc = glGetUniformLocation(m_ShaderID, "gpoint_light.position");
	glUniform3f(m_ColourLoc, light.colour.x, light.colour.y, light.colour.z);
	glUniform1f(m_AmbIntensityLoc, light.ambIntensity);
	glUniform1f(m_DiffIntensityLoc, light.diffIntensity);
	glUniform3f(m_posLoc, light.center.x, light.center.y, light.center.z);

}