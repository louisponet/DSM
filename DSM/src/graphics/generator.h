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

	void initStructureCoordinateSystemBufs(Structure* structure);
	void setupStructureCoordinateSystemBufs(Structure* structure);

	void createHUDRectangle(glm::vec3 start,float width, float height,glm::vec3 colour, std::vector<glm::vec3>* verts,std::vector<glm::vec3>* colours);
	void create2DStructureCylinder(glm::vec3 v1, glm::vec3 v2, glm::vec3 colour, VAO* vao, std::vector<VBO*> vbos);
	void create2DStructureCone(glm::vec3 v1, glm::vec3 v2, glm::vec3 colour, VAO* vao, std::vector<VBO*> vbos);
	void create2DStructureSphere(glm::vec3 center, float radius, glm::vec3 colour, VAO* vao, std::vector<VBO*> vbos);
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
