
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

void Generator::setupBuf(VBO *buf, float *bufBeginning, GLuint size)
{
	buf->bind();
	buf->submitData(bufBeginning, size);
	buf->unbind();
}



void Generator::initStructureBufs(Structure* structure)
{
	m_glWidget->makeCurrent();
	for (unsigned int i = 0; i < 3; i++)
	{
		VAO* vao = new VAO();
		VBO* vertBuf = new VBO(GL_ARRAY_BUFFER);
		VBO* indBuf = new VBO(GL_ELEMENT_ARRAY_BUFFER);
		VBO* colBuf= new VBO(GL_ARRAY_BUFFER); 
		VBO* normBuf = new VBO(GL_ARRAY_BUFFER);
		VBO* matBuf = new VBO(GL_ARRAY_BUFFER);
		VBO* intBuf = new VBO(GL_ARRAY_BUFFER);
		VBO* powBuf= new VBO(GL_ARRAY_BUFFER);
		vao->create();
		structure->vaos.push_back(vao);
		vao->bind();
		vertBuf->create();
		indBuf->create();
		normBuf->create();
		colBuf->create();
		matBuf->create();
		intBuf->create();
		powBuf->create();
		GLint size;
		if(i==0)
		{
			size = structure->getAtoms().size();
			
		}
		else if(i == 1)
		{
			size = structure->getBonds().size();
		}
		else
		{
			size = structure->cubes.size();
		}
		vertBuf->bind();
		vertBuf->allocate(BaseSphere::instance()->getVertices().size() * sizeof(glm::vec3)*(structure->imMats.size() + 1), GL_DYNAMIC_DRAW);
		indBuf->bind();
		indBuf->allocate(BaseSphere::instance()->getIndices().size() * sizeof(GLuint)*(structure->imMats.size() + 1), GL_DYNAMIC_DRAW);
		normBuf->bind();
		normBuf->allocate(BaseSphere::instance()->getNormals().size() * sizeof(glm::vec3)*(structure->imMats.size() + 1), GL_DYNAMIC_DRAW);
		colBuf->bind();
		colBuf->allocate(size * sizeof(glm::vec3)*(structure->imMats.size() + 1), GL_DYNAMIC_DRAW);
		matBuf->bind();
		matBuf->allocate(size * sizeof(glm::mat4)*(structure->imMats.size() + 1), GL_DYNAMIC_DRAW);
		intBuf->bind();
		intBuf->allocate(size * sizeof(GLfloat)*(structure->imMats.size() + 1), GL_DYNAMIC_DRAW);
		powBuf->bind();
		powBuf->allocate(size * sizeof(GLfloat)*(structure->imMats.size() + 1), GL_DYNAMIC_DRAW);
		structure->vertBufs.push_back(vertBuf);
		structure->indBufs.push_back(indBuf);
		structure->colBufs.push_back(colBuf);
		structure->normBufs.push_back(normBuf);
		structure->matBufs.push_back(matBuf);
		structure->intBufs.push_back(intBuf);
		structure->powBufs.push_back(powBuf);
	}
	VBO* numBuf = new VBO(GL_ARRAY_BUFFER);
	numBuf->create();
	numBuf->bind();
	numBuf->allocate(structure->spheres.size() * sizeof(GLfloat)*(structure->imMats.size() + 1),GL_DYNAMIC_DRAW);
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
		structure->colBufs[i]->del();
		structure->matBufs[i]->del();
		structure->intBufs[i]->del();
		structure->powBufs[i]->del();
		structure->colBufs[i]->create();
		structure->matBufs[i]->create();
		structure->intBufs[i]->create();
		structure->powBufs[i]->create();
		structure->colBufs[i]->bind();
		structure->colBufs[i]->allocate(size*sizeof(glm::vec3)*(structure->imMats.size() + 1), GL_DYNAMIC_DRAW);
		structure->matBufs[i]->bind();
		structure->matBufs[i]->allocate(size * sizeof(glm::mat4)*(structure->imMats.size() + 1), GL_DYNAMIC_DRAW);
		structure->intBufs[i]->bind();
		structure->intBufs[i]->allocate(size * sizeof(GLfloat)*(structure->imMats.size() + 1),  GL_DYNAMIC_DRAW);
		structure->powBufs[i]->bind();
		structure->powBufs[i]->allocate(size * sizeof(GLfloat)*(structure->imMats.size() + 1), GL_DYNAMIC_DRAW);

	}
	structure->numberBufs[0]->del();
	structure->numberBufs[0]->create();
	structure->numberBufs[0]->bind();
	structure->numberBufs[0]->allocate(structure->spheres.size()*sizeof(GLfloat)*(structure->imMats.size() + 1), GL_DYNAMIC_DRAW);
	structure->numberBufs[0]->unbind();
	m_glWidget->doneCurrent();

}

void Generator::deleteCylinderBufs(Structure *structure)
{
    m_glWidget->makeCurrent();
    structure->colBufs[1]->del();
    structure->indBufs[1]->del();
    structure->normBufs[1]->del();
    structure->vertBufs[1]->del();
    structure->matBufs[1]->del();
    structure->intBufs[1]->del();
    structure->powBufs[1]->del();
    structure->vaos[1]->del();

    structure->vaos[1]->create();
    structure->vaos[1]->bind();

    structure->colBufs[1]->create();
    structure->indBufs[1]->create();
    structure->normBufs[1]->create();
    structure->vertBufs[1]->create();
    structure->matBufs[1]->create();
    structure->intBufs[1]->create();
    structure->powBufs[1]->create();
	structure->vaos[1]->unbind();
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cout << "OpenGL Error while deleting cylinder buffers: " << error << std::endl;
    }
    m_glWidget->doneCurrent();
}



void Generator::setupCylinderBufs(Structure *structure)
{
    m_glWidget->makeCurrent();
    std::vector<glm::vec3>cylVertices = BaseCylinder::instance()->getVertices();
    std::vector<glm::vec3> cylNormals = BaseCylinder::instance()->getNormals();
    std::vector<glm::mat4>& imMats = structure->imMats;
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
        structure->vaos[1]->bind();
        setupBuf(structure->vertBufs[1],&cylVertices[0][0],cylVertices.size()*sizeof(glm::vec3));
        setupBuf(structure->colBufs[1],&cylColours[0],cylColours.size()*sizeof(GLfloat));
        setupBuf(structure->normBufs[1],&cylNormals[0][0],cylNormals.size()*sizeof(glm::vec3));
        setupBuf(structure->matBufs[1],&cylMats[0][0][0],cylMats.size() * sizeof(glm::mat4));
        setupBuf(structure->intBufs[1],&cylInts[0],cylInts.size() * sizeof(GLfloat));
        setupBuf(structure->powBufs[1],&cylPows[0],cylPows.size()*sizeof(GLfloat));
		structure->vaos[1]->submitVBO(structure->vertBufs[1], VAO::VERT);
		structure->vaos[1]->submitVBO(structure->colBufs[1], VAO::COL);
		structure->vaos[1]->submitVBO(structure->normBufs[1], VAO::NORM);
		structure->vaos[1]->submitVBO(structure->matBufs[1], VAO::MAT);
		structure->vaos[1]->submitVBO(structure->intBufs[1], VAO::INT);
		structure->vaos[1]->submitVBO(structure->powBufs[1], VAO::POW);
		

    }
    else
    {
//        structure->vaos[1].bind();
//        setupVaoVertBuf(&structure->vertBufs[1],NULL,cylVertices.size());
//        setupVaoColBuf(&structure->colBufs[1],NULL,cylColours.size());
//        setupVaoNormBuf(&structure->normBufs[1],NULL,cylNormals.size());
//        setupVaoMatBuf(&structure->matBufs[1],NULL,cylMats.size());
//        setupVaoIntBuf(&structure->intBufs[1],NULL,cylInts.size());
//        setupVaoPowBuf(&structure->powBufs[1],NULL,cylPows.size());
    }
    std::vector<GLuint> indices = BaseCylinder::instance()->getIndices();
    structure->indBufs[1]->bind();
	structure->indBufs[1]->allocate(indices.size() * sizeof(GLuint), GL_DYNAMIC_DRAW);
	structure->indBufs[1]->submitData(&indices[0], indices.size() * sizeof(GLuint));
	structure->indBufs[1]->unbind();
    structure->numVertsList[1]=indices.size();
	structure->vaos[1]->unbind();
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error while setting up cylinder buffers: " << error << std::endl;
	}
    glBindBuffer(GL_ARRAY_BUFFER,0);

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
	structure->vaos[0]->bind();
	structure->matBufs[0]->bind();
	structure->matBufs[0]->allocate(mats.size() * sizeof(glm::mat4), GL_DYNAMIC_DRAW);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error while updating Structure buffers: " << error << std::endl;
	}
    setupBuf(structure->matBufs[0],&mats[0][0][0],mats.size()*sizeof(glm::mat4));
	structure->vaos[0]->submitVBO(structure->matBufs[0], VAO::MAT);
    setupCylinderBufs(structure);
	structure->vaos[0]->unbind();

	m_glWidget->doneCurrent();

	m_glWidget->update();

}

void Generator::genVaos(Structure* structure)
{	
	m_glWidget->makeCurrent();
#if _DEBUG
	Timer timer;
#endif // _DEBUG
	std::vector<std::vector<glm::vec3>>vertices;
	std::vector<std::vector<GLfloat>>colours;
	std::vector<std::vector<glm::vec3>>normals;
	std::vector<std::vector<glm::mat4>>matrices;
	std::vector<std::vector<GLfloat>>ints;
	std::vector<std::vector<GLfloat>>pows;
	std::vector<std::vector<GLuint>>indices;


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
	vertices.push_back(sphVertices);
	colours.push_back(sphColours);
	normals.push_back(sphNormals);
	matrices.push_back(sphMats);
	ints.push_back(sphInts);
	pows.push_back(sphPows);
	indices.push_back(sphIndices);
	structure->numVertsList.push_back(sphIndices.size());
	structure->numObjsList.push_back(sphPows.size());

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
		structure->numVertsList.push_back(cylIndices.size());
		structure->numObjsList.push_back(cylPows.size());
		vertices.push_back(cylVertices);
		colours.push_back(cylColours);
		normals.push_back(cylNormals);
		matrices.push_back(cylMats);
		ints.push_back(cylInts);
		pows.push_back(cylPows);
		indices.push_back(cylIndices);
	}

	std::vector<glm::vec3> cubVertices = BaseCube::instance()->getVertices();
	std::vector < glm::vec3 > cubNormals = BaseCube::instance()->getNormals();
	std::vector<GLuint> cubIndices = BaseCube::instance()->getIndices();
	std::vector<GLfloat> cubColours;
	std::vector<GLfloat> cubInts;
	std::vector<GLfloat> cubPows;
	std::vector<glm::mat4> cubMats;

	for (unsigned int i = 0; i < cubes.size(); i++)
	{
		cubColours.push_back(cubes[i].colour.x);
		cubColours.push_back(cubes[i].colour.y);
		cubColours.push_back(cubes[i].colour.z);
		cubInts.push_back(cubes[i].specIntensity);
		cubPows.push_back(cubes[i].specPower);
		cubMats.push_back(cubes[i].mat);
		for (unsigned int i1 = 0; i1<imMats.size(); i1++)
		{
			cubColours.push_back(cubes[i].colour.x);
			cubColours.push_back(cubes[i].colour.y);
			cubColours.push_back(cubes[i].colour.z);
			cubInts.push_back(cubes[i].specIntensity);
			cubPows.push_back(cubes[i].specPower);
			cubMats.push_back(imMats[i1] * cubes[i].mat);
		}
	}
	structure->numVertsList.push_back(cubIndices.size());
	structure->numObjsList.push_back(cubPows.size());
	vertices.push_back(cubVertices);
	colours.push_back(cubColours);
	normals.push_back(cubNormals);
	matrices.push_back(cubMats);
	ints.push_back(cubInts);
	pows.push_back(cubPows);
	indices.push_back(cubIndices);
	for (int i = 0; i < 3; i++)
	{
		if (cylinders.empty())
		{
			i -= 1;
			continue;
		}
		structure->vaos[i]->bind();
	
		structure->vertBufs[i]->bind();
		structure->vertBufs[i]->submitData(&vertices[i][0][0], vertices[i].size() * sizeof(glm::vec3));
		structure->vaos[i]->submitVBO(structure->vertBufs[i], VAO::VERT);
	
		structure->colBufs[i]->bind();
		structure->colBufs[i]->submitData(&colours[i][0], colours[i].size() * sizeof(GLfloat));
		structure->vaos[i]->submitVBO(structure->colBufs[i], VAO::COL);

		structure->normBufs[i]->bind();
		structure->normBufs[i]->submitData(&normals[i][0][0], normals[i].size() * sizeof(glm::vec3));
		structure->vaos[i]->submitVBO(structure->normBufs[i], VAO::NORM);

		structure->matBufs[i]->bind();
		structure->matBufs[i]->submitData(&matrices[i][0][0][0], matrices[i].size() * sizeof(glm::mat4));
		structure->vaos[i]->submitVBO(structure->matBufs[i], VAO::MAT);

		structure->intBufs[i]->bind();
		structure->intBufs[i]->submitData(&ints[i][0], ints[i].size() * sizeof(GLfloat));
		structure->vaos[i]->submitVBO(structure->intBufs[i], VAO::INT);

		structure->powBufs[i]->bind();
		structure->powBufs[i]->submitData(&pows[i][0], pows[i].size() * sizeof(GLfloat));
		structure->vaos[i]->submitVBO(structure->powBufs[i], VAO::POW);
		if (i == 0)
		{
			structure->numberBufs[0]->bind();
			structure->numberBufs[0]->submitData(&sphNumbers[0], sphNumbers.size() * sizeof(GLfloat));
			structure->vaos[0]->submitVBO(structure->numberBufs[0], VAO::NUM);
		}

		structure->indBufs[i]->bind();
		structure->indBufs[i]->submitData(&indices[i][0], indices[i].size() * sizeof(GLuint));
	

	}
	
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error1: " << error << std::endl;
	}
//	if (!cylinders.empty())
//	{
//		std::vector<glm::vec3>cylVertices = BaseCylinder::instance()->getVertices();
//		std::vector<glm::vec3> cylNormals = BaseCylinder::instance()->getNormals();
//		std::vector<GLuint> cylIndices = BaseCylinder::instance()->getIndices();
//		std::vector<GLfloat> cylColours;
//		std::vector<GLfloat> cylInts;
//		std::vector<GLfloat> cylPows;
//		std::vector<glm::mat4> cylMats;
//
//		for (unsigned int i = 0; i < cylinders.size(); i++)
//		{
//			cylColours.push_back(cylinders[i].colour.x / 65535.0f);
//			cylColours.push_back(cylinders[i].colour.y / 65535.0f);
//			cylColours.push_back(cylinders[i].colour.z / 65535.0f);
//			cylInts.push_back(cylinders[i].specIntensity);
//			cylPows.push_back(cylinders[i].specPower);
//			cylMats.push_back(cylinders[i].mat);
//			for (unsigned int i1 =0; i1<imMats.size();i1++)
//			{
//				cylColours.push_back(cylinders[i].colour.x / 65535.0f);
//				cylColours.push_back(cylinders[i].colour.y / 65535.0f);
//				cylColours.push_back(cylinders[i].colour.z / 65535.0f);
//				cylInts.push_back(cylinders[i].specIntensity);
//				cylPows.push_back(cylinders[i].specPower);
//				cylMats.push_back(imMats[i1]*cylinders[i].mat);
//			}
//
//
//		}
//		structure->numVertsList.push_back(cylIndices.size());
//		structure->numObjsList.push_back(cylPows.size());
//
//		glBindVertexArray(structure->vaos[1]);
//		glBindBuffer(GL_ARRAY_BUFFER, structure->vertBufs[1]);
//		glBufferSubData(GL_ARRAY_BUFFER,0, cylVertices.size() * sizeof(glm::vec3), &cylVertices[0]);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//		glBindBuffer(GL_ARRAY_BUFFER, structure->colBufs[1]);
//		glBufferSubData(GL_ARRAY_BUFFER,0, cylColours.size() * sizeof(GLfloat), &cylColours[0]);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//		glBindBuffer(GL_ARRAY_BUFFER, structure->normBufs[1]);
//		glBufferSubData(GL_ARRAY_BUFFER,0, cylNormals.size() * sizeof(glm::vec3), &cylNormals[0]);
//		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//        setupVaoMatBuf(&(structure->matBufs[1]),&cylMats[0][0][0],cylMats.size());
//
//		glBindBuffer(GL_ARRAY_BUFFER, structure->intBufs[1]);
//		glBufferSubData(GL_ARRAY_BUFFER,0, cylInts.size() * sizeof(GLfloat), &cylInts[0]);
//		glVertexAttribPointer(7, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
//		glBindBuffer(GL_ARRAY_BUFFER, structure->powBufs[1]);
//		glBufferSubData(GL_ARRAY_BUFFER,0, cylPows.size() * sizeof(GLfloat), &cylPows[0]);
//		glVertexAttribPointer(8, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
//		glEnableVertexAttribArray(0);
//		glEnableVertexAttribArray(1);
//		glEnableVertexAttribArray(2);
//		glEnableVertexAttribArray(3);
//		glEnableVertexAttribArray(4);
//		glEnableVertexAttribArray(5);
//		glEnableVertexAttribArray(6);
//		glEnableVertexAttribArray(7);
//		glEnableVertexAttribArray(8);
//
//		glVertexAttribDivisor(1, 1);
//		glVertexAttribDivisor(3, 1);
//		glVertexAttribDivisor(4, 1);
//		glVertexAttribDivisor(5, 1);
//		glVertexAttribDivisor(6, 1);
//		glVertexAttribDivisor(7, 1);
//		glVertexAttribDivisor(8, 1);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, structure->indBufs[1]);
//		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0, cylIndices.size() * sizeof(GLuint), &cylIndices[0]);
//	}
//	else
//	{
//		structure->numVertsList.push_back(0);
//		structure->numObjsList.push_back(0);
//	}
//	error = glGetError();
//	if (error != GL_NO_ERROR)
//	{
//		std::cout << "OpenGL Error2: " << error << std::endl;
//	}
//
//	std::vector<glm::vec3> cubVertices=BaseCube::instance()->getVertices();
//	std::vector < glm::vec3 > cubNormals = BaseCube::instance()->getNormals();
//	std::vector<GLuint> cubIndices = BaseCube::instance()->getIndices();
//	std::vector<GLfloat> cubColours;
//	std::vector<GLfloat> cubInts;
//	std::vector<GLfloat> cubPows;
//	std::vector<glm::mat4> cubMats;
//
//	for (unsigned int i = 0; i < cubes.size(); i++)
//	{
//        cubColours.push_back(cubes[i].colour.x );
//        cubColours.push_back(cubes[i].colour.y );
//        cubColours.push_back(cubes[i].colour.z );
//		cubInts.push_back(cubes[i].specIntensity);
//		cubPows.push_back(cubes[i].specPower);
//		cubMats.push_back(cubes[i].mat);
//		for (unsigned int i1 = 0;i1<imMats.size();i1++)
//		{
//            cubColours.push_back(cubes[i].colour.x );
//            cubColours.push_back(cubes[i].colour.y );
//            cubColours.push_back(cubes[i].colour.z );
//			cubInts.push_back(cubes[i].specIntensity);
//			cubPows.push_back(cubes[i].specPower);
//			cubMats.push_back(imMats[i1]*cubes[i].mat);
//		}
//	}
//	structure->numVertsList.push_back(cubIndices.size());
//	structure->numObjsList.push_back(cubPows.size());
//
//	glBindVertexArray(structure->vaos[2]);
//	glBindBuffer(GL_ARRAY_BUFFER, structure->vertBufs[2]);
//	glBufferSubData(GL_ARRAY_BUFFER,0, cubVertices.size() * sizeof(glm::vec3), &cubVertices[0]);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//	glBindBuffer(GL_ARRAY_BUFFER, structure->colBufs[2]);
//	glBufferSubData(GL_ARRAY_BUFFER,0, cubColours.size() * sizeof(GLfloat), &cubColours[0]);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//	glBindBuffer(GL_ARRAY_BUFFER, structure->normBufs[2]);
//	glBufferSubData(GL_ARRAY_BUFFER,0, cubNormals.size() * sizeof(glm::vec3), &cubNormals[0]);
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//    setupVaoMatBuf(&(structure->matBufs[2]),&cubMats[0][0][0],cubMats.size());
//	glBindBuffer(GL_ARRAY_BUFFER, structure->intBufs[2]);
//	glBufferSubData(GL_ARRAY_BUFFER,0, cubInts.size() * sizeof(GLfloat), &cubInts[0]);
//	glVertexAttribPointer(7, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
//	glBindBuffer(GL_ARRAY_BUFFER, structure->powBufs[2]);
//	glBufferSubData(GL_ARRAY_BUFFER,0, cubPows.size() * sizeof(GLfloat), &cubPows[0]);
//	glVertexAttribPointer(8, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//	glEnableVertexAttribArray(2);
//	glEnableVertexAttribArray(3);
//	glEnableVertexAttribArray(4);
//	glEnableVertexAttribArray(5);
//	glEnableVertexAttribArray(6);
//	glEnableVertexAttribArray(7);
//	glEnableVertexAttribArray(8);
//
//	glVertexAttribDivisor(1, 1);
//	glVertexAttribDivisor(3, 1);
//	glVertexAttribDivisor(4, 1);
//	glVertexAttribDivisor(5, 1);
//	glVertexAttribDivisor(6, 1);
//	glVertexAttribDivisor(7, 1);
//	glVertexAttribDivisor(8, 1);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, structure->indBufs[2]);
//	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0, cubIndices.size() * sizeof(GLuint), &cubIndices[0]);

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
		structure->colBufs[i]->del();
		structure->indBufs[i]->del();
		structure->normBufs[i]->del();
		structure->vertBufs[i]->del();
		structure->matBufs[i]->del();
		structure->intBufs[i]->del();
		structure->powBufs[i]->del();
		structure->vaos[i]->del();
	}
	structure->numberBufs[0]->del();
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
