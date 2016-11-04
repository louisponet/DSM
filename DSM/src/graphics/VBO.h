#pragma once

#include "GL.h"

class VBO :private GL
{
public:
	VBO(GLenum target);
	~VBO();

	void create();
	void del();
	void bind();
	void unbind();

	void allocate(GLuint size,GLenum usage);
	void submitData(void* data,GLuint size);
	void allocateAndSubmit(void* data, GLuint size, GLenum usage);
private:
	GLenum m_target;
	GLuint m_ID;
};