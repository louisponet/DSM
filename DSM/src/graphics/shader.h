#pragma once
#include <glm/glm.hpp>
#include <QtWidgets/QOpenGLWidget>
#include "light.h"
#include "../graphics/GL.h"



class Shader:protected GL
{
protected:
	GLuint m_ShaderID;
	const char *m_VertPath, *m_FragPath;

	QOpenGLWidget* m_glWidget;
public:
    Shader(const char* vertPath, const char* fragPath);
    Shader();
	~Shader();

	void enable();
	void disable();
	void load(QOpenGLWidget* glwidget);
	
	void setUniform3vec(const  GLchar* uniform, glm::vec3 vec) ;
	void setUniform4mat(const char* uniform, glm::mat4 mat) ;
	

private:
};
