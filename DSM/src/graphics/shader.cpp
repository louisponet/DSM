#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>
#include "../fileio/fileutils.h"
#include "shader.h"
#include "../global.h"
#include <QDir>

Shader::Shader(const char* vertPath, const char* fragPath):
    m_VertPath(vertPath),m_FragPath(fragPath)
{

}

Shader::Shader()
{

}

void Shader::load(QOpenGLWidget* glwidget)
{
	m_glWidget = glwidget;

	initializeOpenGLFunctions();
	m_ShaderID = glCreateProgram();
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    
    std::string vertSourceString = FileUtils::read_file(m_VertPath);
    std::string fragSourceString = FileUtils::read_file(m_FragPath);


	const char* vertSource = vertSourceString.c_str();
	const char* fragSource = fragSourceString.c_str();


	glShaderSource(vertex, 1, &vertSource, NULL);
	glCompileShader(vertex);

	GLint result;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(vertex, length, &length, &error[0]);
		std::cout << "Failed to compile vertex shader!" << std::endl << &error[0] << std::endl;
		glDeleteShader(vertex);

	}

	glShaderSource(fragment, 1, &fragSource, NULL);
	glCompileShader(fragment);


	glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(fragment, length, &length, &error[0]);
		std::cout << "Failed to compile fragment shader!"<<std::endl << &error[0] << std::endl;
		glDeleteShader(fragment);

	}

	glAttachShader(m_ShaderID, vertex);
	glAttachShader(m_ShaderID, fragment);
	
	glLinkProgram(m_ShaderID);
	glValidateProgram(m_ShaderID);
	
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	initLocations();
}

void Shader::initLocations() {
	enable();
	m_SelectedIndexLoc = glGetUniformLocation(m_ShaderID, "selected_index");
	m_ColourLoc = glGetUniformLocation(m_ShaderID, "gpoint_light.colour");
	m_AmbIntensityLoc = glGetUniformLocation(m_ShaderID, "gpoint_light.amb_intensity");
	m_DiffIntensityLoc = glGetUniformLocation(m_ShaderID, "gpoint_light.diff_intensity");
	m_posLoc = glGetUniformLocation(m_ShaderID, "gpoint_light.position");
	disable();
}

void Shader::setSelectedIndex(const unsigned int& index)  {
	
	glUniform1f(m_SelectedIndexLoc, (GLfloat)index);

}

void Shader::setLightProperties(const Light& light)  {
	m_Light = light;

	glUniform3f(m_ColourLoc, light.colour.x, light.colour.y, light.colour.z);
	glUniform1f(m_AmbIntensityLoc, light.ambIntensity);
	glUniform1f(m_DiffIntensityLoc, light.diffIntensity);
	glUniform3f(m_posLoc, light.center.x, light.center.y, light.center.z);

}

void Shader::setUniform3vec(const GLchar* uniform, glm::vec3 vec)  {

	glUniform3fv(glGetUniformLocation(m_ShaderID, uniform), 1,&vec[0]);

	
}

void Shader::setUniform4mat(const char* uniform, glm::mat4 mat)  {

	glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, uniform), 1, GL_FALSE, &mat[0][0]);

}

void Shader::disableDiffuseLighting() {

	glUniform1f(m_DiffIntensityLoc, 0.0f);
	glUniform1f(m_AmbIntensityLoc, 0.4f);

}

void Shader::enableDiffuseLighting() {

	glUniform1f(m_DiffIntensityLoc, m_Light.diffIntensity);
	glUniform1f(m_AmbIntensityLoc, m_Light.ambIntensity);

}


void Shader::enable()  {

	glUseProgram(m_ShaderID);
}

void Shader::disable()  {
	glUseProgram(0);

}

Shader::~Shader()
{
	glDeleteShader(m_ShaderID);
}
