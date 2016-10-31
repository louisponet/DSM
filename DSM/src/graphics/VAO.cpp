#include "VAO.h"

VAO::VAO()
{
	initializeOpenGLFunctions();
}

VAO::~VAO()
{

}

void VAO::create()
{
	glGenVertexArrays(1, &m_ID);
}

void VAO::del()
{
	glDeleteVertexArrays(1, &m_ID);
}

void VAO::bind()
{
	glBindVertexArray(m_ID);
}

void VAO::unbind()
{
	glBindVertexArray(0);

}

void VAO::submitVBO(VBO* vbo, BufferType type)
{
	vbo->bind();
	if (type == VERT)
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
	}
	else if (type == COL)
	{
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribDivisor(1, 1);
	}
	else if (type == NORM)
	{
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(2);
	}
	else if (type == MAT)
	{
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 16*sizeof(GLfloat), (void*)0);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), (void*)(4*sizeof(GLfloat)));
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), (void*)(4*sizeof(GLfloat) * 2));
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), (void*)(4*sizeof(GLfloat) * 3));
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);
		glEnableVertexAttribArray(5);
		glEnableVertexAttribArray(6);
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
	}
	else if (type == INT)
	{
		glVertexAttribPointer(7, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(7);
		glVertexAttribDivisor(7, 1);
	}
	else if (type == POW)
	{
		glVertexAttribPointer(8, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(8);
		glVertexAttribDivisor(8, 1);
	}
	else if (type == NUM)
	{
		glVertexAttribPointer(9, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(9);
		glVertexAttribDivisor(9, 1);
	}
	vbo->unbind();
}