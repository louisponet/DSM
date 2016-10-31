#pragma once

#include <QtWidgets/QOpenGLWidget>
#include "../entities/structure.h"
#include "../graphics/GL.h"
#include "VBO.h"
#include "VAO.h"


class Generator:private GL
{
	static Generator* gen_instance;
public:
	~Generator();
	void init(QOpenGLWidget* widget);
	void initStructureBufs(Structure* structure);
	void regenStructureBufs(Structure* structure);
	void updateStructureBufs(Structure* structure);
    void setupCylinderBufs(Structure* structure);
	void genVao(GLuint& vao,GLuint& indBuf, GLuint& numVertices,GLuint& numObjects,std::vector<Renderable3D>& renderables);
	void genVaos(Structure* structure);
	void deleteStructureBuffers(Structure* structure);
private:
	Generator();
	QOpenGLWidget* m_glWidget;
public:
	static Generator* instance()
	{
		if (!gen_instance)
			gen_instance = new Generator;
		return gen_instance;
	}

    void deleteCylinderBufs(Structure *structure);
private:
    void setupBuf(VBO* buf, float* bufBeginning,GLuint size);

};
