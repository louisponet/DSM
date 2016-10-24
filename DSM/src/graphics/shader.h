#pragma once
#include <glm/glm.hpp>
#include <QOpenGLWidget>
#include "light.h"
#include "../graphics/GL.h"



class Shader:GL
{
private:
	GLuint m_ShaderID, m_SelectedIndexLoc,m_ColourLoc,m_AmbIntensityLoc,m_DiffIntensityLoc,m_posLoc;
	const char *m_VertPath, *m_FragPath;
	Light m_Light;
	QOpenGLWidget* m_glWidget;
public:
	Shader(const char* vertPath, const char* fragPath);
	~Shader();

	void enable();
	void disable();
	void load(QOpenGLWidget* glwidget);
	void setLightProperties(const Light& light) ;
	void setSelectedIndex(const unsigned int& index) ;
	void setUniform3vec(const  GLchar* uniform, glm::vec3& vec) ;
	void setUniform4mat(const char* uniform, glm::mat4& mat) ;
	void disableDiffuseLighting() ;
	void enableDiffuseLighting() ;

private:
	void initLocations();
};