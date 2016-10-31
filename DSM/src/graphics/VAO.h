#pragma once

#include "GL.h"
#include "VBO.h"



class VAO : private GL
{

public:
	enum BufferType
	{
		VERT,
		COL,
		NORM,
		MAT,
		INT,
		POW,
		NUM
	};
private:
	GLuint m_ID;
public:
	VAO();
	~VAO();

	void create();
	void del();

	void bind();
	void unbind();

	void submitVBO(VBO* vbo, BufferType type);
};