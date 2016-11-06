#define COORD_SYSTEM_ORIGIN glm::dvec3(-1.2,-0.8,0.0)
#ifdef _DEBUG
#include "../utils/timer.h"
#endif // _DEBUG
#include <iostream>
#include "../global.h"
#include "../renderables/cone.h"
#include "generator.h"
#include "../utils/maths.h"


Generator::Generator()
{
}

Generator::~Generator()
{

}


void Generator::init(GLWidget* widget)
{
	initializeOpenGLFunctions();
	m_glWidget = widget;
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
		structure->vaos3D.push_back(vao);
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
		structure->vertBufs3D.push_back(vertBuf);
		structure->indBufs3D.push_back(indBuf);
		structure->colBufs3D.push_back(colBuf);
		structure->normBufs3D.push_back(normBuf);
		structure->matBufs3D.push_back(matBuf);
		structure->intBufs3D.push_back(intBuf);
		structure->powBufs3D.push_back(powBuf);
	}
	VBO* numBuf = new VBO(GL_ARRAY_BUFFER);
	numBuf->create();
	numBuf->bind();
	numBuf->allocate(structure->spheres.size() * sizeof(GLfloat)*(structure->imMats.size() + 1),GL_DYNAMIC_DRAW);
	structure->numberBufs3D.push_back(numBuf);

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
		structure->colBufs3D[i]->del();
		structure->matBufs3D[i]->del();
		structure->intBufs3D[i]->del();
		structure->powBufs3D[i]->del();
		structure->colBufs3D[i]->create();
		structure->matBufs3D[i]->create();
		structure->intBufs3D[i]->create();
		structure->powBufs3D[i]->create();
		structure->colBufs3D[i]->bind();
		structure->colBufs3D[i]->allocate(size*sizeof(glm::vec3)*(structure->imMats.size() + 1), GL_DYNAMIC_DRAW);
		structure->matBufs3D[i]->bind();
		structure->matBufs3D[i]->allocate(size * sizeof(glm::mat4)*(structure->imMats.size() + 1), GL_DYNAMIC_DRAW);
		structure->intBufs3D[i]->bind();
		structure->intBufs3D[i]->allocate(size * sizeof(GLfloat)*(structure->imMats.size() + 1),  GL_DYNAMIC_DRAW);
		structure->powBufs3D[i]->bind();
		structure->powBufs3D[i]->allocate(size * sizeof(GLfloat)*(structure->imMats.size() + 1), GL_DYNAMIC_DRAW);

	}
	structure->numberBufs3D[0]->del();
	structure->numberBufs3D[0]->create();
	structure->numberBufs3D[0]->bind();
	structure->numberBufs3D[0]->allocate(structure->spheres.size()*sizeof(GLfloat)*(structure->imMats.size() + 1), GL_DYNAMIC_DRAW);
	structure->numberBufs3D[0]->unbind();
	m_glWidget->doneCurrent();

}

void Generator::deleteCylinderBufs(Structure *structure)
{
    m_glWidget->makeCurrent();
    structure->colBufs3D[1]->del();
    structure->indBufs3D[1]->del();
    structure->normBufs3D[1]->del();
    structure->vertBufs3D[1]->del();
    structure->matBufs3D[1]->del();
    structure->intBufs3D[1]->del();
    structure->powBufs3D[1]->del();
    structure->vaos3D[1]->del();

    structure->vaos3D[1]->create();
    structure->vaos3D[1]->bind();

    structure->colBufs3D[1]->create();
    structure->indBufs3D[1]->create();
    structure->normBufs3D[1]->create();
    structure->vertBufs3D[1]->create();
    structure->matBufs3D[1]->create();
    structure->intBufs3D[1]->create();
    structure->powBufs3D[1]->create();
	structure->vaos3D[1]->unbind();
#ifdef _DEBUG
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error trying to render2D: " << error << std::endl;
	}
#endif
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
    structure->numObjsList3D[1] = cylPows.size();
    if (!cylinders.empty())
    {
        structure->vaos3D[1]->bind();
		structure->vertBufs3D[1]->bind();
		structure->vertBufs3D[1]->allocate(cylVertices.size() * sizeof(glm::vec3), GL_DYNAMIC_DRAW);
		structure->vertBufs3D[1]->submitData(&cylVertices[0][0], cylVertices.size() * sizeof(glm::vec3));
		structure->colBufs3D[1]->bind();
		structure->colBufs3D[1]->allocate(cylColours.size() * sizeof(GLfloat), GL_DYNAMIC_DRAW);
		structure->colBufs3D[1]->submitData(&cylColours[0], cylColours.size() * sizeof(GLfloat));
		structure->normBufs3D[1]->bind();
		structure->normBufs3D[1]->allocate(cylNormals.size() * sizeof(glm::vec3), GL_DYNAMIC_DRAW);
		structure->normBufs3D[1]->submitData(&cylNormals[0][0], cylNormals.size() * sizeof(glm::vec3));
		structure->matBufs3D[1]->bind();
		structure->matBufs3D[1]->allocate(cylMats.size() * sizeof(glm::mat4), GL_DYNAMIC_DRAW);
		structure->matBufs3D[1]->submitData(&cylMats[0][0][0], cylMats.size() * sizeof(glm::mat4));
		structure->intBufs3D[1]->bind();
		structure->intBufs3D[1]->allocate(cylInts.size() * sizeof(GLfloat), GL_DYNAMIC_DRAW);
		structure->intBufs3D[1]->submitData(&cylInts[0], cylInts.size() * sizeof(GLfloat));
		structure->powBufs3D[1]->bind();
		structure->powBufs3D[1]->allocate(cylPows.size() * sizeof(GLfloat), GL_DYNAMIC_DRAW);
		structure->powBufs3D[1]->submitData(&cylPows[0], cylPows.size() * sizeof(GLfloat));
		structure->vaos3D[1]->submitVBO(structure->vertBufs3D[1], VAO::VERT);
		structure->vaos3D[1]->submitVBO(structure->colBufs3D[1], VAO::COL);
		structure->vaos3D[1]->submitVBO(structure->normBufs3D[1], VAO::NORM);
		structure->vaos3D[1]->submitVBO(structure->matBufs3D[1], VAO::MAT);
		structure->vaos3D[1]->submitVBO(structure->intBufs3D[1], VAO::INT);
		structure->vaos3D[1]->submitVBO(structure->powBufs3D[1], VAO::POW);
#ifdef _DEBUG
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "OpenGL Error trying to render2D: " << error << std::endl;
		}
#endif
		glBindBuffer(GL_ARRAY_BUFFER,0);
		

    }
    else
    {
//        structure->vaos[1].bind();
//        setupVaoVertBuf(&structure->vertBufs3D[1],NULL,cylVertices.size());
//        setupVaoColBuf(&structure->colBufs3D[1],NULL,cylColours.size());
//        setupVaoNormBuf(&structure->normBufs3D[1],NULL,cylNormals.size());
//        setupVaoMatBuf(&structure->matBufs3D[1],NULL,cylMats.size());
//        setupVaoIntBuf(&structure->intBufs3D[1],NULL,cylInts.size());
//        setupVaoPowBuf(&structure->powBufs3D[1],NULL,cylPows.size());
    }
    std::vector<GLuint> indices = BaseCylinder::instance()->getIndices();
    structure->indBufs3D[1]->bind();
	structure->indBufs3D[1]->allocate(indices.size() * sizeof(GLuint), GL_DYNAMIC_DRAW);
	structure->indBufs3D[1]->submitData(&indices[0], indices.size() * sizeof(GLuint));
	structure->indBufs3D[1]->unbind();
    structure->numVertsList3D[1]=indices.size();
	structure->vaos3D[1]->unbind();

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
	structure->vaos3D[0]->bind();
	structure->matBufs3D[0]->bind();
	structure->matBufs3D[0]->allocate(mats.size() * sizeof(glm::mat4), GL_DYNAMIC_DRAW);
	structure->matBufs3D[0]->submitData(&mats[0][0][0], mats.size() * sizeof(glm::mat4));
	structure->matBufs3D[0]->unbind();
	structure->vaos3D[0]->submitVBO(structure->matBufs3D[0], VAO::MAT);
    setupCylinderBufs(structure);
	structure->vaos3D[0]->unbind();
#ifdef _DEBUG
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error trying to render2D: " << error << std::endl;
	}
#endif

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
	structure->numObjsList3D.clear();
	structure->numVertsList3D.clear();
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
	structure->numVertsList3D.push_back(sphIndices.size());
	structure->numObjsList3D.push_back(sphPows.size());

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
		structure->numVertsList3D.push_back(cylIndices.size());
		structure->numObjsList3D.push_back(cylPows.size());
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
	structure->numVertsList3D.push_back(cubIndices.size());
	structure->numObjsList3D.push_back(cubPows.size());
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
		structure->vaos3D[i]->bind();
	
		structure->vertBufs3D[i]->bind();
		structure->vertBufs3D[i]->submitData(&vertices[i][0][0], vertices[i].size() * sizeof(glm::vec3));
		structure->vaos3D[i]->submitVBO(structure->vertBufs3D[i], VAO::VERT);
	
		structure->colBufs3D[i]->bind();
		structure->colBufs3D[i]->submitData(&colours[i][0], colours[i].size() * sizeof(GLfloat));
		structure->vaos3D[i]->submitVBO(structure->colBufs3D[i], VAO::COL);

		structure->normBufs3D[i]->bind();
		structure->normBufs3D[i]->submitData(&normals[i][0][0], normals[i].size() * sizeof(glm::vec3));
		structure->vaos3D[i]->submitVBO(structure->normBufs3D[i], VAO::NORM);

		structure->matBufs3D[i]->bind();
		structure->matBufs3D[i]->submitData(&matrices[i][0][0][0], matrices[i].size() * sizeof(glm::mat4));
		structure->vaos3D[i]->submitVBO(structure->matBufs3D[i], VAO::MAT);

		structure->intBufs3D[i]->bind();
		structure->intBufs3D[i]->submitData(&ints[i][0], ints[i].size() * sizeof(GLfloat));
		structure->vaos3D[i]->submitVBO(structure->intBufs3D[i], VAO::INT);

		structure->powBufs3D[i]->bind();
		structure->powBufs3D[i]->submitData(&pows[i][0], pows[i].size() * sizeof(GLfloat));
		structure->vaos3D[i]->submitVBO(structure->powBufs3D[i], VAO::POW);
		if (i == 0)
		{
			structure->numberBufs3D[0]->bind();
			structure->numberBufs3D[0]->submitData(&sphNumbers[0], sphNumbers.size() * sizeof(GLfloat));
			structure->vaos3D[0]->submitVBO(structure->numberBufs3D[0], VAO::NUM);
		}

		structure->indBufs3D[i]->bind();
		structure->indBufs3D[i]->submitData(&indices[i][0], indices[i].size() * sizeof(GLuint));
	

	}
	
#ifdef _DEBUG
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error trying to render2D: " << error << std::endl;
	}
#endif
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
#ifdef _DEBUG
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error trying to render2D: " << error << std::endl;
	}
#endif
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
		structure->colBufs3D[i]->del();
		structure->indBufs3D[i]->del();
		structure->normBufs3D[i]->del();
		structure->vertBufs3D[i]->del();
		structure->matBufs3D[i]->del();
		structure->intBufs3D[i]->del();
		structure->powBufs3D[i]->del();
		structure->vaos3D[i]->del();
	}
	structure->numberBufs3D[0]->del();
	m_glWidget->doneCurrent();
}

void Generator::create2DStructureCylinder(glm::vec3 v1, glm::vec3 v2, glm::vec3 colour, VAO* vao, std::vector<VBO*> vbos)
{
	m_glWidget->makeCurrent();

	Cylinder cylinder(v1, v2, 0.01f, colour, 0.9f, 10.0f, Cylinder::NORMAL);

	vao->create();
	vao->bind();
	for (int i = 0; i < vbos.size(); i++)
	{
		vbos[i]->create();
	}

	vbos[0]->bind();
	vbos[0]->allocateAndSubmit(&cylinder.vertices[0][0], cylinder.vertices.size() * sizeof(glm::vec3), GL_STATIC_DRAW);
	vao->submitVBO(vbos[0], VAO::VERT);


	vbos[1]->bind();
	vbos[1]->allocateAndSubmit(&cylinder.colour[0], sizeof(glm::vec3), GL_STATIC_DRAW);
	vao->submitVBO(vbos[1], VAO::COL);

	vbos[2]->bind();
	vbos[2]->allocateAndSubmit(&cylinder.normals[0][0], cylinder.normals.size() * sizeof(glm::vec3), GL_STATIC_DRAW);
	vao->submitVBO(vbos[2], VAO::NORM);

	vbos[3]->bind();
	vbos[3]->allocateAndSubmit(&cylinder.mat[0][0], sizeof(glm::mat4), GL_STATIC_DRAW);
	vao->submitVBO(vbos[3], VAO::MAT);

	vbos[4]->bind();
	vbos[4]->allocateAndSubmit(&cylinder.specIntensity, sizeof(GLfloat), GL_STATIC_DRAW);
	vao->submitVBO(vbos[4], VAO::INT);

	vbos[5]->bind();
	vbos[5]->allocateAndSubmit(&cylinder.specPower, sizeof(GLfloat), GL_STATIC_DRAW);
	vao->submitVBO(vbos[5], VAO::POW);
	vbos[5]->unbind();
	
	vbos[6]->bind();
	vbos[6]->allocateAndSubmit(&cylinder.indices[0], cylinder.indices.size() * sizeof(GLuint), GL_STATIC_DRAW);
	vbos[6]->unbind();
	vao->unbind();
	m_glWidget->doneCurrent();


}

void Generator::create2DStructureCone(glm::vec3 v1, glm::vec3 v2, glm::vec3 colour, VAO* vao, std::vector<VBO*> vbos)
{
	m_glWidget->makeCurrent();

	Cone cone(v1, v2, 0.01f, colour, 0.9f, 10.0f);

	vao->create();
	vao->bind();

	for (int i = 0; i < vbos.size(); i++)
	{
		vbos[i]->create();
	}


	vbos[0]->bind();
	vbos[0]->allocateAndSubmit(&cone.vertices[0][0], cone.vertices.size() * sizeof(glm::vec3), GL_STATIC_DRAW);
	vao->submitVBO(vbos[0], VAO::VERT);


	vbos[1]->bind();
	vbos[1]->allocateAndSubmit(&cone.colour[0], sizeof(glm::vec3), GL_STATIC_DRAW);
	vao->submitVBO(vbos[1], VAO::COL);

	vbos[2]->bind();
	vbos[2]->allocateAndSubmit(&cone.normals[0][0], cone.normals.size() * sizeof(glm::vec3), GL_STATIC_DRAW);
	vao->submitVBO(vbos[2], VAO::NORM);

	vbos[3]->bind();
	vbos[3]->allocateAndSubmit(&cone.mat[0][0], sizeof(glm::mat4), GL_STATIC_DRAW);
	vao->submitVBO(vbos[3], VAO::MAT);

	vbos[4]->bind();
	vbos[4]->allocateAndSubmit(&cone.specIntensity, sizeof(GLfloat), GL_STATIC_DRAW);
	vao->submitVBO(vbos[4], VAO::INT);

	vbos[5]->bind();
	vbos[5]->allocateAndSubmit(&cone.specPower, sizeof(GLfloat), GL_STATIC_DRAW);
	vao->submitVBO(vbos[5], VAO::POW);
	vbos[5]->unbind();

	vbos[6]->bind();
	vbos[6]->allocateAndSubmit(&cone.indices[0], cone.indices.size() * sizeof(GLuint), GL_STATIC_DRAW);
	vbos[6]->unbind();
	vao->unbind();
	m_glWidget->doneCurrent();

}

void Generator::create2DStructureSphere(glm::vec3 center, float radius, glm::vec3 colour,VAO* vao,std::vector<VBO*> vbos)
{
	m_glWidget->makeCurrent();

	Sphere sphere(center, radius, colour, 0.9f, 10.0f, 100000);

	vao->create();
	vao->bind();

	for (int i = 0; i < vbos.size(); i++)
	{
		vbos[i]->create();
	}

	vbos[0]->bind();
	vbos[0]->allocateAndSubmit(&sphere.vertices[0][0], sphere.vertices.size() * sizeof(glm::vec3), GL_STATIC_DRAW);
	vao->submitVBO(vbos[0], VAO::VERT);


	vbos[1]->bind();
	vbos[1]->allocateAndSubmit(&sphere.colour[0], sizeof(glm::vec3), GL_STATIC_DRAW);
	vao->submitVBO(vbos[1], VAO::COL);

	vbos[2]->bind();
	vbos[2]->allocateAndSubmit(&sphere.normals[0][0], sphere.normals.size() * sizeof(glm::vec3), GL_STATIC_DRAW);
	vao->submitVBO(vbos[2], VAO::NORM);

	vbos[3]->bind();
	vbos[3]->allocateAndSubmit(&sphere.mat[0][0], sizeof(glm::mat4), GL_STATIC_DRAW);
	vao->submitVBO(vbos[3], VAO::MAT);

	vbos[4]->bind();
	vbos[4]->allocateAndSubmit(&sphere.specIntensity, sizeof(GLfloat), GL_STATIC_DRAW);
	vao->submitVBO(vbos[4], VAO::INT);

	vbos[5]->bind();
	vbos[5]->allocateAndSubmit(&sphere.specPower, sizeof(GLfloat), GL_STATIC_DRAW);
	vao->submitVBO(vbos[5], VAO::POW);
	vbos[5]->unbind();

	vbos[6]->bind();
	vbos[6]->allocateAndSubmit(&sphere.indices[0], sphere.indices.size() * sizeof(GLuint), GL_STATIC_DRAW);
	vbos[6]->unbind();
	vao->unbind();
	m_glWidget->doneCurrent();
}

void Generator::createAndSubmit2DSphere(glm::vec3 center, float radius, glm::vec3 colour)
{
	m_glWidget->makeCurrent();

	Sphere sphere(center,radius,colour, 0.9f, 10.0f,100000);
	VAO* vao = new VAO();
	VBO* vertBuf = new VBO(GL_ARRAY_BUFFER);
	VBO* indBuf = new VBO(GL_ELEMENT_ARRAY_BUFFER);
	VBO* colBuf = new VBO(GL_ARRAY_BUFFER);
	VBO* normBuf = new VBO(GL_ARRAY_BUFFER);
	VBO* matBuf = new VBO(GL_ARRAY_BUFFER);
	VBO* intBuf = new VBO(GL_ARRAY_BUFFER);
	VBO* powBuf = new VBO(GL_ARRAY_BUFFER);

	vao->create();
	vao->bind();

	vertBuf->create();
	indBuf->create();
	normBuf->create();
	colBuf->create();
	matBuf->create();
	intBuf->create();
	powBuf->create();

	vertBuf->bind();
	vertBuf->allocateAndSubmit(&sphere.vertices[0][0], sphere.vertices.size() * sizeof(glm::vec3), GL_STATIC_DRAW);
	vao->submitVBO(vertBuf, VAO::VERT);

	indBuf->bind();
	indBuf->allocateAndSubmit(&sphere.indices[0], sphere.indices.size() * sizeof(GLuint), GL_STATIC_DRAW);
	indBuf->unbind();

	colBuf->bind();
	colBuf->allocateAndSubmit(&sphere.colour[0], sizeof(glm::vec3), GL_STATIC_DRAW);
	vao->submitVBO(colBuf, VAO::COL);

	normBuf->bind();
	normBuf->allocateAndSubmit(&sphere.normals[0][0], sphere.normals.size() * sizeof(glm::vec3), GL_STATIC_DRAW);
	vao->submitVBO(normBuf, VAO::NORM);

	matBuf->bind();
	matBuf->allocateAndSubmit(&sphere.mat[0][0], sizeof(glm::mat4), GL_STATIC_DRAW);
	vao->submitVBO(matBuf, VAO::MAT);

	intBuf->bind();
	intBuf->allocateAndSubmit(&sphere.specIntensity, sizeof(GLfloat), GL_STATIC_DRAW);
	vao->submitVBO(intBuf, VAO::INT);

	powBuf->bind();
	powBuf->allocateAndSubmit(&sphere.specPower, sizeof(GLfloat), GL_STATIC_DRAW);
	vao->submitVBO(powBuf, VAO::POW);
	powBuf->unbind();
	vao->unbind();
	m_glWidget->submit2DVao(vao, indBuf, sphere.indices.size());
	m_glWidget->doneCurrent();

}



void Generator::createAndSubmit2DVector(glm::vec3 v1,glm::vec3 v2, glm::vec3 colour,Direction direction)
{
	
}

void Generator::setupStructureCoordinateSystem(Structure* structure)
{
	m_glWidget->makeCurrent();

	std::vector<VBO*> temp_vbos;
	for (int i = 0; i < 7; i++)
	{
		VAO* vao = new VAO();
		VBO* vertBuf = new VBO(GL_ARRAY_BUFFER);
		VBO* indBuf = new VBO(GL_ELEMENT_ARRAY_BUFFER);
		VBO* colBuf = new VBO(GL_ARRAY_BUFFER);
		VBO* normBuf = new VBO(GL_ARRAY_BUFFER);
		VBO* matBuf = new VBO(GL_ARRAY_BUFFER);
		VBO* intBuf = new VBO(GL_ARRAY_BUFFER);
		VBO* powBuf = new VBO(GL_ARRAY_BUFFER);
		structure->vertBufs2D.push_back(vertBuf);
		structure->indBufs2D.push_back(indBuf);
		structure->colBufs2D.push_back(colBuf);
		structure->normBufs2D.push_back(normBuf);
		structure->matBufs2D.push_back(matBuf);
		structure->intBufs2D.push_back(intBuf);
		structure->powBufs2D.push_back(powBuf);
		structure->vaos2D.push_back(vao);
	}

	temp_vbos.push_back(structure->vertBufs2D[0]);
	temp_vbos.push_back(structure->colBufs2D[0]);
	temp_vbos.push_back(structure->normBufs2D[0]);
	temp_vbos.push_back(structure->matBufs2D[0]);
	temp_vbos.push_back(structure->intBufs2D[0]);
	temp_vbos.push_back(structure->powBufs2D[0]);
	temp_vbos.push_back(structure->indBufs2D[0]);
	create2DStructureSphere(COORD_SYSTEM_ORIGIN,0.01f,glm::vec3(1.0f),structure->vaos2D[0],temp_vbos);
	temp_vbos.clear();
	structure->numObjsList2D.push_back(1);
	structure->numVertsList2D.push_back(BaseSphere::instance()->getIndices().size());

	temp_vbos.push_back(structure->vertBufs2D[1]);
	temp_vbos.push_back(structure->colBufs2D[1]);
	temp_vbos.push_back(structure->normBufs2D[1]);
	temp_vbos.push_back(structure->matBufs2D[1]);
	temp_vbos.push_back(structure->intBufs2D[1]);
	temp_vbos.push_back(structure->powBufs2D[1]);
	temp_vbos.push_back(structure->indBufs2D[1]);
	create2DStructureCylinder(COORD_SYSTEM_ORIGIN, COORD_SYSTEM_ORIGIN + glm::normalize(structure->getCell()[0])/10.0, glm::vec3(1.0f, 0.0f,0.0f), structure->vaos2D[1], temp_vbos);
	temp_vbos.clear();
	temp_vbos.push_back(structure->vertBufs2D[4]);
	temp_vbos.push_back(structure->colBufs2D[4]);
	temp_vbos.push_back(structure->normBufs2D[4]);
	temp_vbos.push_back(structure->matBufs2D[4]);
	temp_vbos.push_back(structure->intBufs2D[4]);
	temp_vbos.push_back(structure->powBufs2D[4]);
	temp_vbos.push_back(structure->indBufs2D[4]);
	create2DStructureCone(COORD_SYSTEM_ORIGIN + glm::normalize(structure->getCell()[0])/10.0, COORD_SYSTEM_ORIGIN + (glm::normalize(structure->getCell()[0])+ 0.2* glm::normalize(structure->getCell()[0]))/10.0, glm::vec3(1.0f, 0.0f, 0.0f), structure->vaos2D[4], temp_vbos);
	temp_vbos.clear();
	structure->numObjsList2D.push_back(1);
	structure->numObjsList2D.push_back(1);
	structure->numVertsList2D.push_back(BaseCylinder::instance()->getIndices().size());
	structure->numVertsList2D.push_back(BaseCone::instance()->getIndices().size());

	temp_vbos.push_back(structure->vertBufs2D[2]);
	temp_vbos.push_back(structure->colBufs2D[2]);
	temp_vbos.push_back(structure->normBufs2D[2]);
	temp_vbos.push_back(structure->matBufs2D[2]);
	temp_vbos.push_back(structure->intBufs2D[2]);
	temp_vbos.push_back(structure->powBufs2D[2]);
	temp_vbos.push_back(structure->indBufs2D[2]);
	create2DStructureCylinder(COORD_SYSTEM_ORIGIN, COORD_SYSTEM_ORIGIN + maths::convertZupToZback(glm::normalize(structure->getCell()[1])/10.0), glm::vec3(0.0f, 1.0f,0.0f), structure->vaos2D[2], temp_vbos);
	temp_vbos.clear();
	temp_vbos.push_back(structure->vertBufs2D[5]);
	temp_vbos.push_back(structure->colBufs2D[5]);
	temp_vbos.push_back(structure->normBufs2D[5]);
	temp_vbos.push_back(structure->matBufs2D[5]);
	temp_vbos.push_back(structure->intBufs2D[5]);
	temp_vbos.push_back(structure->powBufs2D[5]);
	temp_vbos.push_back(structure->indBufs2D[5]);
	create2DStructureCone(COORD_SYSTEM_ORIGIN + maths::convertZupToZback(glm::normalize(structure->getCell()[1])/10.0), COORD_SYSTEM_ORIGIN + maths::convertZupToZback(glm::normalize(structure->getCell()[1]) + 0.2* glm::normalize(structure->getCell()[1]))/10.0, glm::vec3(0.0f, 1.0f, 0.0f), structure->vaos2D[5], temp_vbos);
	temp_vbos.clear();
	structure->numObjsList2D.push_back(1);
	structure->numObjsList2D.push_back(1);
	structure->numVertsList2D.push_back(BaseCylinder::instance()->getIndices().size());
	structure->numVertsList2D.push_back(BaseCone::instance()->getIndices().size());

	temp_vbos.push_back(structure->vertBufs2D[3]);
	temp_vbos.push_back(structure->colBufs2D[3]);
	temp_vbos.push_back(structure->normBufs2D[3]);
	temp_vbos.push_back(structure->matBufs2D[3]);
	temp_vbos.push_back(structure->intBufs2D[3]);
	temp_vbos.push_back(structure->powBufs2D[3]);
	temp_vbos.push_back(structure->indBufs2D[3]);
	create2DStructureCylinder(COORD_SYSTEM_ORIGIN, COORD_SYSTEM_ORIGIN + maths::convertZupToZback(glm::normalize(structure->getCell()[2])/10.0), glm::vec3(0.0f,0.0f,1.0f), structure->vaos2D[3], temp_vbos);
	temp_vbos.clear();
	temp_vbos.push_back(structure->vertBufs2D[6]);
	temp_vbos.push_back(structure->colBufs2D[6]);
	temp_vbos.push_back(structure->normBufs2D[6]);
	temp_vbos.push_back(structure->matBufs2D[6]);
	temp_vbos.push_back(structure->intBufs2D[6]);
	temp_vbos.push_back(structure->powBufs2D[6]);
	temp_vbos.push_back(structure->indBufs2D[6]);
	create2DStructureCone(COORD_SYSTEM_ORIGIN + maths::convertZupToZback(glm::normalize(structure->getCell()[2])/10.0), COORD_SYSTEM_ORIGIN + maths::convertZupToZback((glm::normalize(structure->getCell()[2]) + 0.2*glm::normalize(structure->getCell()[2]))/10.0), glm::vec3(0.0f, 0.0f, 1.0f), structure->vaos2D[6], temp_vbos);
	temp_vbos.clear();
	structure->numObjsList2D.push_back(1);
	structure->numObjsList2D.push_back(1);
	structure->numVertsList2D.push_back(BaseCylinder::instance()->getIndices().size());
	structure->numVertsList2D.push_back(BaseCone::instance()->getIndices().size());
	m_glWidget->doneCurrent();

}