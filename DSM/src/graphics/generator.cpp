
#ifdef _DEBUG
#include "../utils/timer.h"
#endif // _DEBUG
#include <iostream>
#include "../global.h"
#include "generator.h"

Generator::Generator()
{
}

Generator::~Generator()
{

}


void Generator::init(QOpenGLWidget* widget)
{
	initializeOpenGLFunctions();
	m_glWidget = widget;
}

void Generator::initStructureBufs(Structure* structure)
{
	m_glWidget->makeCurrent();
	for (unsigned int i = 0; i < 3; i++)
	{
		GLuint vao;
		GLuint vertBuf, indBuf, colBuf, normBuf, matBuf, intBuf, powBuf;
		glGenVertexArrays(1, &vao);
		structure->vaos.push_back(vao);
		glBindVertexArray(vao);
		glGenBuffers(1, &vertBuf);
		glGenBuffers(1, &indBuf);
		glGenBuffers(1, &normBuf);
		glGenBuffers(1, &colBuf);
		glGenBuffers(1, &matBuf);
		glGenBuffers(1, &intBuf);
		glGenBuffers(1, &powBuf);
		if(i==0)
		{
			GLint size = structure->getAtoms().size();
			glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
			glBufferData(GL_ARRAY_BUFFER, BaseSphere::instance()->getVertices().size()*sizeof(glm::vec3)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBuf);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, BaseSphere::instance()->getIndices().size()*sizeof(GLuint)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, normBuf);
			glBufferData(GL_ARRAY_BUFFER, BaseSphere::instance()->getNormals().size()*sizeof(glm::vec3)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, colBuf);
			glBufferData(GL_ARRAY_BUFFER, size*sizeof(glm::vec3)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, matBuf);
			glBufferData(GL_ARRAY_BUFFER, size*sizeof(glm::mat4)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, intBuf);
			glBufferData(GL_ARRAY_BUFFER, size*sizeof(GLfloat)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, powBuf);
			glBufferData(GL_ARRAY_BUFFER, size*sizeof(GLfloat)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
		}
		else if(i == 1)
		{
			GLint size = structure->getBonds().size();
			glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
			glBufferData(GL_ARRAY_BUFFER,BaseCylinder::instance()->getVertices().size() * sizeof(glm::vec3)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBuf);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, BaseCylinder::instance()->getIndices().size() * sizeof(GLuint)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, normBuf);
			glBufferData(GL_ARRAY_BUFFER, BaseCylinder::instance()->getNormals().size() * sizeof(glm::vec3)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, colBuf);
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(glm::vec3)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, matBuf);
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(glm::mat4)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, intBuf);
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, powBuf);
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
		}
		else
		{
			GLint size = structure->cubes.size();
			glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
			glBufferData(GL_ARRAY_BUFFER, BaseCube::instance()->getVertices().size() * sizeof(glm::vec3)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBuf);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, BaseCube::instance()->getIndices().size() * sizeof(GLuint)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, normBuf);
			glBufferData(GL_ARRAY_BUFFER, BaseCube::instance()->getNormals().size() * sizeof(glm::vec3)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, colBuf);
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(glm::vec3)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, matBuf);
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(glm::mat4)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, intBuf);
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, powBuf);
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
		}

		structure->vertBufs.push_back(vertBuf);
		structure->indBufs.push_back(indBuf);
		structure->colBufs.push_back(colBuf);
		structure->normBufs.push_back(normBuf);
		structure->matBufs.push_back(matBuf);
		structure->intBufs.push_back(intBuf);
		structure->powBufs.push_back(powBuf);
	}
	GLuint numBuf;
	glGenBuffers(1, &numBuf);
	glBindBuffer(GL_ARRAY_BUFFER, numBuf);
	glBufferData(GL_ARRAY_BUFFER, structure->spheres.size()* sizeof(GLfloat)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
	structure->numberBufs.push_back(numBuf);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error0: " << error << std::endl;
	}
	m_glWidget->doneCurrent();
}

void Generator::regenStructureBufs(Structure* structure)
{

	m_glWidget->makeCurrent();
	for (unsigned int i = 0; i < 3; i++)
	{
		GLint size;
		if (i==0)
		{
			size = structure->spheres.size();
		}
		else if (i == 1)
		{
			size = structure->cylinders.size()*2;
		}
		else if (i==2)
		{
			size = structure->cubes.size();
		}
		glDeleteBuffers(1, &structure->colBufs[i]);
		glDeleteBuffers(1, &structure->matBufs[i]);
		glDeleteBuffers(1, &structure->intBufs[i]);
		glDeleteBuffers(1, &structure->powBufs[i]);
		glGenBuffers(1, &structure->colBufs[i]);
		glGenBuffers(1, &structure->matBufs[i]);
		glGenBuffers(1, &structure->intBufs[i]);
		glGenBuffers(1, &structure->powBufs[i]);
		glBindBuffer(GL_ARRAY_BUFFER, structure->colBufs[i]);
		glBufferData(GL_ARRAY_BUFFER, size*sizeof(glm::vec3)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, structure->matBufs[i]);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(glm::mat4)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, structure->intBufs[i]);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, structure->powBufs[i]);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);

	}
	glDeleteBuffers(1, &structure->numberBufs[0]);
	glGenBuffers(1, &structure->numberBufs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, structure->numberBufs[0]);
	glBufferData(GL_ARRAY_BUFFER, structure->spheres.size()*sizeof(GLfloat)*(structure->imMats.size() + 1), NULL, GL_DYNAMIC_DRAW);
	m_glWidget->doneCurrent();

}

void Generator::updateStructureBufs(Structure* structure)
{
	std::vector<glm::mat4>& imMats = structure->imMats;
	std::vector<Sphere>& spheres = structure->spheres;
	m_glWidget->makeCurrent();
	std::vector<glm::mat4> mats;
	mats.reserve(spheres.size() +(spheres.size() * imMats.size()));
	for (int i = 0; i < spheres.size(); i++)
	{
		mats.push_back(spheres[i].mat);
		for (int i1 = 0; i1 < imMats.size(); i1++)
			mats.push_back(imMats[i1] * spheres[i].mat);
	}
	glBindVertexArray(structure->vaos[0]);

	glBindBuffer(GL_ARRAY_BUFFER, structure->matBufs[0]);
	glBufferSubData(GL_ARRAY_BUFFER,0, mats.size() * sizeof(glm::mat4), &mats[0][0][0]);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 2));
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 3));
	std::vector<Cylinder>& cylinders = structure->cylinders;
	std::vector<GLfloat> cylColours;
	cylColours.reserve(cylinders.size() + (cylinders.size()*imMats.size()));
	std::vector<GLfloat> cylInts;
	cylInts.reserve(cylinders.size() + (cylinders.size()*imMats.size()));
	std::vector<GLfloat> cylPows;
	cylPows.reserve(cylinders.size() + (cylinders.size()*imMats.size()));
	std::vector<glm::mat4> cylMats;
	cylMats.reserve(cylinders.size() + (cylinders.size()*imMats.size()));
	for (unsigned int i = 0; i < cylinders.size(); i++)
	{
		cylColours.push_back(cylinders[i].colour.x / 65535.0f);
		cylColours.push_back(cylinders[i].colour.y / 65535.0f);
		cylColours.push_back(cylinders[i].colour.z / 65535.0f);
		cylInts.push_back(cylinders[i].specIntensity);
		cylPows.push_back(cylinders[i].specPower);
		cylMats.push_back(cylinders[i].mat);
		for (unsigned int i1 = 0; i1 < imMats.size(); i1++)
		{
			cylColours.push_back(cylinders[i].colour.x / 65535.0f);
			cylColours.push_back(cylinders[i].colour.y / 65535.0f);
			cylColours.push_back(cylinders[i].colour.z / 65535.0f);
			cylInts.push_back(cylinders[i].specIntensity);
			cylPows.push_back(cylinders[i].specPower);
			cylMats.push_back(imMats[i1] * cylinders[i].mat);
		}
	}
	structure->numObjsList[1] = cylPows.size();
	if (!cylinders.empty())
	{
		glBindVertexArray(structure->vaos[1]);
		glBindBuffer(GL_ARRAY_BUFFER, structure->colBufs[1]);
		glBufferData(GL_ARRAY_BUFFER, cylColours.size() * sizeof(GLfloat), &cylColours[0],GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, structure->matBufs[1]);
		glBufferData(GL_ARRAY_BUFFER, cylMats.size() * sizeof(glm::mat4), &cylMats[0][0][0],GL_DYNAMIC_DRAW);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 2));
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 3));
		glBindBuffer(GL_ARRAY_BUFFER, structure->intBufs[1]);
		glBufferData(GL_ARRAY_BUFFER, cylInts.size() * sizeof(GLfloat), &cylInts[0],GL_DYNAMIC_DRAW);
		glVertexAttribPointer(7, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, structure->powBufs[1]);
		glBufferData(GL_ARRAY_BUFFER, cylPows.size() * sizeof(GLfloat), &cylPows[0],GL_DYNAMIC_DRAW);
		glVertexAttribPointer(8, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
	else
	{
		glBindVertexArray(structure->vaos[1]);
		glBindBuffer(GL_ARRAY_BUFFER, structure->colBufs[1]);
		glBufferData(GL_ARRAY_BUFFER, cylColours.size() * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, structure->matBufs[1]);
		glBufferData(GL_ARRAY_BUFFER, cylMats.size() * sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 2));
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 3));
		glBindBuffer(GL_ARRAY_BUFFER, structure->intBufs[1]);
		glBufferData(GL_ARRAY_BUFFER, cylInts.size() * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(7, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, structure->powBufs[1]);
		glBufferData(GL_ARRAY_BUFFER, cylPows.size() * sizeof(GLfloat),NULL, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(8, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	m_glWidget->doneCurrent();

	m_glWidget->update();

}

void Generator::genVaos(Structure* structure)
{	
	m_glWidget->makeCurrent();
#if _DEBUG
	Timer timer;
#endif // _DEBUG
	std::vector<Sphere> spheres = structure->spheres;
	std::vector<Cylinder> cylinders = structure->cylinders;
	std::vector<Cube> cubes = structure->cubes;
	structure->numObjsList.clear();
	structure->numVertsList.clear();
	std::vector<glm::mat4> imMats = structure->imMats;
	std::vector < glm::vec3 >sphVertices=BaseSphere::instance()->getVertices();
	std::vector<glm::vec3>sphNormals= BaseSphere::instance()->getNormals();
	std::vector<GLuint> sphIndices= BaseSphere::instance()->getIndices();
	std::vector<GLfloat> sphColours;
	std::vector<GLfloat> sphInts;
	std::vector<GLfloat> sphPows;
	std::vector<GLfloat> sphNumbers;
	std::vector<glm::mat4> sphMats;
	for (unsigned int i = 0; i < spheres.size(); i++)
	{
		sphColours.push_back(spheres[i].colour.x / 65535.0f);
		sphColours.push_back(spheres[i].colour.y / 65535.0f);
		sphColours.push_back(spheres[i].colour.z / 65535.0f);
		sphInts.push_back(spheres[i].specIntensity);
		sphPows.push_back(spheres[i].specPower);
		sphNumbers.push_back((GLfloat)spheres[i].index);
		sphMats.push_back(spheres[i].mat);
		for (unsigned int i1 = 0 ; i1<imMats.size();i1++)
		{
			sphColours.push_back(spheres[i].colour.x / 65535.0f);
			sphColours.push_back(spheres[i].colour.y / 65535.0f);
			sphColours.push_back(spheres[i].colour.z / 65535.0f);
			sphInts.push_back(spheres[i].specIntensity);
			sphPows.push_back(spheres[i].specPower);
			sphNumbers.push_back(spheres[i].index);
			sphMats.push_back(imMats[i1]*spheres[i].mat);
		}

	}

	structure->numVertsList.push_back(sphIndices.size());
	structure->numObjsList.push_back(sphPows.size());
	glBindVertexArray(structure->vaos[0]);

	glBindBuffer(GL_ARRAY_BUFFER, structure->vertBufs[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sphVertices.size() * sizeof(glm::vec3), &sphVertices[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, structure->colBufs[0]);
	glBufferSubData(GL_ARRAY_BUFFER,0, sphColours.size() * sizeof(GLfloat), &sphColours[0]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, structure->normBufs[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sphNormals.size() * sizeof(glm::vec3), &sphNormals[0]);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, structure->matBufs[0]);
	glBufferSubData(GL_ARRAY_BUFFER,0, sphMats.size() * sizeof(glm::mat4), &sphMats[0][0][0]);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE,  sizeof(glm::mat4), (void*)0);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 2));
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 3));
	glBindBuffer(GL_ARRAY_BUFFER, structure->intBufs[0]);
	glBufferSubData(GL_ARRAY_BUFFER,0, sphInts.size() * sizeof(GLfloat), &sphInts[0]);
	glVertexAttribPointer(7, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, structure->powBufs[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0,sphPows.size() * sizeof(GLfloat), &sphPows[0]);
	glVertexAttribPointer(8, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, structure->numberBufs[0]);
	glBufferSubData(GL_ARRAY_BUFFER,0, sphNumbers.size() * sizeof(GLfloat), &sphNumbers[0]);
	glVertexAttribPointer(9, 1, GL_FLOAT, GL_FALSE, 0 , (void*)0);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glEnableVertexAttribArray(6);
	glEnableVertexAttribArray(7);
	glEnableVertexAttribArray(8);
	glEnableVertexAttribArray(9);
	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
	glVertexAttribDivisor(7, 1);
	glVertexAttribDivisor(8, 1);
	glVertexAttribDivisor(9, 1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, structure->indBufs[0]);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0, sphIndices.size() * sizeof(GLuint), &sphIndices[0]);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error1: " << error << std::endl;
	}
	
	if (!cylinders.empty())
	{
		std::vector<glm::vec3>cylVertices = BaseCylinder::instance()->getVertices();
		std::vector<glm::vec3> cylNormals = BaseCylinder::instance()->getNormals();
		std::vector<GLuint> cylIndices = BaseCylinder::instance()->getIndices();
		std::vector<GLfloat> cylColours;
		std::vector<GLfloat> cylInts;
		std::vector<GLfloat> cylPows;
		std::vector<glm::mat4> cylMats;

		for (unsigned int i = 0; i < cylinders.size(); i++)
		{
			cylColours.push_back(cylinders[i].colour.x / 65535.0f);
			cylColours.push_back(cylinders[i].colour.y / 65535.0f);
			cylColours.push_back(cylinders[i].colour.z / 65535.0f);
			cylInts.push_back(cylinders[i].specIntensity);
			cylPows.push_back(cylinders[i].specPower);
			cylMats.push_back(cylinders[i].mat);
			for (unsigned int i1 =0; i1<imMats.size();i1++)
			{
				cylColours.push_back(cylinders[i].colour.x / 65535.0f);
				cylColours.push_back(cylinders[i].colour.y / 65535.0f);
				cylColours.push_back(cylinders[i].colour.z / 65535.0f);
				cylInts.push_back(cylinders[i].specIntensity);
				cylPows.push_back(cylinders[i].specPower);
				cylMats.push_back(imMats[i1]*cylinders[i].mat);
			}


		}
		structure->numVertsList.push_back(cylIndices.size());
		structure->numObjsList.push_back(cylPows.size());

		glBindVertexArray(structure->vaos[1]);
		glBindBuffer(GL_ARRAY_BUFFER, structure->vertBufs[1]);
		glBufferSubData(GL_ARRAY_BUFFER,0, cylVertices.size() * sizeof(glm::vec3), &cylVertices[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, structure->colBufs[1]);
		glBufferSubData(GL_ARRAY_BUFFER,0, cylColours.size() * sizeof(GLfloat), &cylColours[0]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, structure->normBufs[1]);
		glBufferSubData(GL_ARRAY_BUFFER,0, cylNormals.size() * sizeof(glm::vec3), &cylNormals[0]);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, structure->matBufs[1]);
		glBufferSubData(GL_ARRAY_BUFFER, 0,cylMats.size() * sizeof(glm::mat4), &cylMats[0][0][0]);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE,sizeof(glm::mat4), (void*)0);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE,sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE,sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 2));
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE,sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 3));
		glBindBuffer(GL_ARRAY_BUFFER, structure->intBufs[1]);
		glBufferSubData(GL_ARRAY_BUFFER,0, cylInts.size() * sizeof(GLfloat), &cylInts[0]);
		glVertexAttribPointer(7, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, structure->powBufs[1]);
		glBufferSubData(GL_ARRAY_BUFFER,0, cylPows.size() * sizeof(GLfloat), &cylPows[0]);
		glVertexAttribPointer(8, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);
		glEnableVertexAttribArray(5);
		glEnableVertexAttribArray(6);
		glEnableVertexAttribArray(7);
		glEnableVertexAttribArray(8);

		glVertexAttribDivisor(1, 1);
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
		glVertexAttribDivisor(7, 1);
		glVertexAttribDivisor(8, 1);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, structure->indBufs[1]);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0, cylIndices.size() * sizeof(GLuint), &cylIndices[0]);
	}
	else
	{
		structure->numVertsList.push_back(0);
		structure->numObjsList.push_back(0);
	}
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error2: " << error << std::endl;
	}

	std::vector<glm::vec3> cubVertices=BaseCube::instance()->getVertices();
	std::vector < glm::vec3 > cubNormals = BaseCube::instance()->getNormals();
	std::vector<GLuint> cubIndices = BaseCube::instance()->getIndices();
	std::vector<GLfloat> cubColours;
	std::vector<GLfloat> cubInts;
	std::vector<GLfloat> cubPows;
	std::vector<glm::mat4> cubMats;

	for (unsigned int i = 0; i < cubes.size(); i++)
	{
		cubColours.push_back(cubes[i].colour.x / 10.0f);
		cubColours.push_back(cubes[i].colour.y / 10.0f);
		cubColours.push_back(cubes[i].colour.z / 10.0f);
		cubInts.push_back(cubes[i].specIntensity);
		cubPows.push_back(cubes[i].specPower);
		cubMats.push_back(cubes[i].mat);
		for (unsigned int i1 = 0;i1<imMats.size();i1++)
		{
			cubColours.push_back(cubes[i].colour.x / 10.0f);
			cubColours.push_back(cubes[i].colour.y / 10.0f);
			cubColours.push_back(cubes[i].colour.z / 10.0f);
			cubInts.push_back(cubes[i].specIntensity);
			cubPows.push_back(cubes[i].specPower);
			cubMats.push_back(imMats[i1]*cubes[i].mat);
		}
	}
	structure->numVertsList.push_back(cubIndices.size());
	structure->numObjsList.push_back(cubPows.size());

	glBindVertexArray(structure->vaos[2]);
	glBindBuffer(GL_ARRAY_BUFFER, structure->vertBufs[2]);
	glBufferSubData(GL_ARRAY_BUFFER,0, cubVertices.size() * sizeof(glm::vec3), &cubVertices[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, structure->colBufs[2]);
	glBufferSubData(GL_ARRAY_BUFFER,0, cubColours.size() * sizeof(GLfloat), &cubColours[0]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, structure->normBufs[2]);
	glBufferSubData(GL_ARRAY_BUFFER,0, cubNormals.size() * sizeof(glm::vec3), &cubNormals[0]);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, structure->matBufs[2]);
	glBufferSubData(GL_ARRAY_BUFFER,0, cubMats.size() * sizeof(glm::mat4), &cubMats[0][0][0]);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE,sizeof(glm::mat4), (void*)0);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE,sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE,sizeof(glm::mat4), (void*)(sizeof(glm::vec4)*2));
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE,sizeof(glm::mat4), (void*)(sizeof(glm::vec4)*3));
	glBindBuffer(GL_ARRAY_BUFFER, structure->intBufs[2]);
	glBufferSubData(GL_ARRAY_BUFFER,0, cubInts.size() * sizeof(GLfloat), &cubInts[0]);
	glVertexAttribPointer(7, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, structure->powBufs[2]);
	glBufferSubData(GL_ARRAY_BUFFER,0, cubPows.size() * sizeof(GLfloat), &cubPows[0]);
	glVertexAttribPointer(8, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glEnableVertexAttribArray(6);
	glEnableVertexAttribArray(7);
	glEnableVertexAttribArray(8);

	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
	glVertexAttribDivisor(7, 1);
	glVertexAttribDivisor(8, 1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, structure->indBufs[2]);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0, cubIndices.size() * sizeof(GLuint), &cubIndices[0]);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error3: " << error << std::endl;
	}
#if _DEBUG
std::cout << "generating buffers took: " << timer.elapsed() << std::endl;
#endif // _DEBUG
	m_glWidget->doneCurrent();
	m_glWidget->update();
}

void Generator::deleteStructureBuffers(Structure * structure)
{
	m_glWidget->makeCurrent();
	for (int i = 0; i < 3; i++)
	{
		glDeleteBuffers(1, &structure->colBufs[i]);
		glDeleteBuffers(1, &structure->indBufs[i]);
		glDeleteBuffers(1, &structure->normBufs[i]);
		glDeleteBuffers(1, &structure->vertBufs[i]);
		glDeleteBuffers(1, &structure->matBufs[i]);
		glDeleteBuffers(1, &structure->intBufs[i]);
		glDeleteBuffers(1, &structure->powBufs[i]);
		glDeleteVertexArrays(1, &structure->vaos[i]);
	}
	glDeleteBuffers(1, &structure->numberBufs[0]);
	m_glWidget->doneCurrent();
}

// void Generator::genVao(GLuint& vao,GLuint& indBuf, GLuint& numVertices, GLuint& numObjects, std::vector<Renderable3D>& renderables)
// {
// 	std::vector<glm::vec3> vertices, normals, colours;
// 	std::vector<glm::mat4>mats;
// 	std::vector<GLuint> indices;
// 	std::vector<GLuint> numbers;
// 	std::vector<GLfloat> specInts, specPows;
// 	for (unsigned int i = 0; i < renderables.size(); i++)
// 	{
// 		vertices.insert(vertices.end(), renderables[i].vertices.begin(), renderables[i].vertices.end()); 
// 		normals.insert(normals.end(), renderables[i].normals.begin(), renderables[i].normals.end());
// 		indices.insert(indices.end(), renderables[i].indices.begin(), renderables[i].indices.end());
// 		colours.push_back(renderables[i].colour);
// 		specInts.push_back(renderables[i].specIntensity);
// 		specPows.push_back(renderables[i].specPower);
// 		mats.push_back(renderables[i].mat);
// 		numbers.push_back(renderables[i].index);
// 	}
// 
// 	glBindVertexArray(vao);
// 	GLuint vertBuf, colBuf, normBuf, matBuf, intBuf, powBuf, numBuf;
// 	glGenBuffers(1, &vertBuf);
// 	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
// 	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0][0], GL_STATIC_DRAW);
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
// 	glGenBuffers(1, &colBuf);
// 	glBindBuffer(GL_ARRAY_BUFFER, colBuf);
// 	glBufferData(GL_ARRAY_BUFFER, colours.size()*sizeof(glm::vec3), &colours[0][0], GL_STATIC_DRAW);
// 	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
// 	glGenBuffers(1, &normBuf);
// 	glBindBuffer(GL_ARRAY_BUFFER, normBuf);
// 	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0][0], GL_STATIC_DRAW);
// 	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
// 	glGenBuffers(1, &matBuf);
// 	glBindBuffer(GL_ARRAY_BUFFER, matBuf);
// 	glBufferData(GL_ARRAY_BUFFER, mats.size()*sizeof(glm::mat4), &mats[0][0][0], GL_STATIC_DRAW);
// 	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
// 	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)16);
// 	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)32);
// 	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)48);
// 	glGenBuffers(1, &intBuf);
// 	glBindBuffer(GL_ARRAY_BUFFER, intBuf);
// 	glBufferData(GL_ARRAY_BUFFER, specInts.size()*sizeof(GLfloat), &specInts[0], GL_STATIC_DRAW);
// 	glVertexAttribPointer(7, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
// 	glGenBuffers(1, &powBuf);
// 	glBindBuffer(GL_ARRAY_BUFFER, powBuf);
// 	glBufferData(GL_ARRAY_BUFFER, specPows.size()*sizeof(GLfloat), &specPows[0], GL_STATIC_DRAW);
// 	glVertexAttribPointer(8, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
// 	glGenBuffers(1, &numBuf);
// 	glBindBuffer(GL_ARRAY_BUFFER, numBuf);
// 	glBufferData(GL_ARRAY_BUFFER, indices.size()*sizeof(GLuint), &numbers[0], GL_STATIC_DRAW);
// 	glVertexAttribPointer(9, 1, GL_UNSIGNED_INT, GL_FALSE, 0, (void*)0);
// 
// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBuf);
// 	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
// 	glEnableVertexAttribArray(0);
// 	glEnableVertexAttribArray(1);
// 	glEnableVertexAttribArray(2);
// 	glEnableVertexAttribArray(3);
// 	glEnableVertexAttribArray(4);
// 	glEnableVertexAttribArray(5);
// 	glEnableVertexAttribArray(6);
// 	glEnableVertexAttribArray(7);
// 	glEnableVertexAttribArray(8);
// 	glEnableVertexAttribArray(9);
// 	/*glVertexAttribDivisor(0, 1);*/
// 	glVertexAttribDivisor(1, 1);
// /*	glVertexAttribDivisor(2, 1);*/
// 	glVertexAttribDivisor(3, 1);
// 	glVertexAttribDivisor(4, 1);
// 	glVertexAttribDivisor(5, 1);
// 	glVertexAttribDivisor(6, 1);
// 	glVertexAttribDivisor(7, 1);
// 	glVertexAttribDivisor(8, 1);
// 	glVertexAttribDivisor(9, 1);
// 	numVertices = indices.size();
// 	numObjects = numbers.size();
// 	glBindBuffer(GL_ARRAY_BUFFER,0);
// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
// 	glBindVertexArray(0);
// }