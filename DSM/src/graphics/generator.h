#pragma once

#include "../graphics/glwidget.h"
#include "../entities/structure.h"
#include "../graphics/GL.h"
#include "VBO.h"
#include "VAO.h"


class Generator:private GL
{
	static Generator* gen_instance;
public:
	enum Direction {
		X, Y, Z
	};
	~Generator();
	void init(GLWidget* widget);
	void initStructureBufs(Structure* structure);
	void regenStructureBufs(Structure* structure);
	void updateStructureBufs(Structure* structure);
    void setupCylinderBufs(Structure* structure);
	void genVao(GLuint& vao,GLuint& indBuf, GLuint& numVertices,GLuint& numObjects,std::vector<Renderable3D>& renderables);
	void genVaos(Structure* structure);
	void deleteStructureBuffers(Structure* structure);
    void deleteCylinderBufs(Structure *structure);

	void createCylinder(glm::vec3 v1, glm::vec3 v2, glm::vec3 colour);
	void createCone(glm::vec3 v1, glm::vec3 v2, glm::vec3 colour);
	void createAndSubmit2DSphere(glm::vec3 center, float radius, glm::vec3 colour);
	void createAndSubmit2DVector(glm::vec3 v1, glm::vec3 v2, glm::vec3 colour,Direction direction);
private:
	Generator();
	GLWidget* m_glWidget;
public:
	
	static Generator* instance()
	{
		if (!gen_instance)
			gen_instance = new Generator;
		return gen_instance;
	}

private:
   

};
