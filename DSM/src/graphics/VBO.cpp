#include "VBO.h"

VBO::VBO(GLenum target):m_target(target)
{
	initializeOpenGLFunctions();
}

VBO::~VBO()
{

}

void VBO::create()
{
	glGenBuffers(1, &m_ID);
}

void VBO::del()
{
	glDeleteBuffers(1, &m_ID);
}

void VBO::bind()
{
	glBindBuffer(m_target, m_ID);
}

void VBO::unbind()
{
	glBindBuffer(m_target, 0);
}

void VBO::allocate(GLuint size, GLenum usage)
{

	glBufferData(m_target, size, NULL, usage);

}

void VBO::submitData(void* data, GLuint size)
{
	glBufferSubData(m_target, 0, size, data);
}