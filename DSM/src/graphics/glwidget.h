#pragma once
#ifndef __APPLE__
#include "../utils/timer.h"
#endif
#include <QtWidgets/QOpenGLWidget>
#include <vector>
#include <QtGui/QMouseEvent>
#include "GL.h"
#include "shader3D.h"
#include "shader2D.h"
#include "../entities/structure.h"

#include "camera.h"


class MainWindow;

class GLWidget : public QOpenGLWidget, public GL
{
	Q_OBJECT

private:
	std::vector<VAO*>* m_3DVaos;
	std::vector<VAO*>* m_2DVaos;
	std::vector<VBO*>* m_3DIndBufs;
	std::vector<VBO*>* m_2DIndBufs;
	std::vector<GLuint>* m_3DNumVerticesList, *m_3DNumObjectsList;
	std::vector<GLuint>* m_2DNumVerticesList ,*m_2DNumObjectsList;
	std::vector<Structure*> m_Structures;
	GLuint m_Vao,m_IndBuf, m_NumVertices, m_NumObjects;
	QPoint m_LastPos;
	Shader3D m_3DShader;
	Shader2D m_2DShader;
	Camera* m_Camera = NULL;

	Light m_Light;
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_OrthogonalMatrix;
	bool m_Testing = false;
	Timer m_Timer;
	int m_SelectedStructure = -1;
public:

	uint selectedIndex=100000;

	bool showCell = true;

private:
	void resizeGL(int w, int h) Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;
	void initializeGL() Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
	void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
	glm::vec4 calculateMouseRay(float x, float y);
public:
	explicit GLWidget(QWidget *parent = Q_NULLPTR);
	~GLWidget();


	void updateSelectedAtom(unsigned int& selectedAtom);
	void addStructure(Structure* structure);
	void removeStructure(int index);
	void selectStructure(int index);
	void submit2DVao(VAO* vao,VBO* indBuf, GLuint numIndices);
	void render3D();
	void render2D();
signals:
	void mouseClicked(glm::vec4 mouseRay, glm::vec3 cameraPos, glm::mat4 globalTransMat);
	void atomMoved(glm::vec3 direction);
};