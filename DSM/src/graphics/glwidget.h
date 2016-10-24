#pragma once

#include <QOpenGLWidget>
#include <vector>
#include <QtGui/QMouseEvent>
#include "GL.h"
#include "shader.h"
#include "../entities/structure.h"
#include "camera.h"
#include "../utils/timer.h"


class MainWindow;

class GLWidget : public QOpenGLWidget, public GL
{
	Q_OBJECT

private:
	std::vector<GLuint>* m_Vaos,*m_IndBufs;
	std::vector<GLuint>* m_NumVerticesList , *m_NumObjectsList;
	std::vector<Structure*> m_Structures;
	GLuint m_Vao,m_IndBuf, m_NumVertices, m_NumObjects;
	QPoint m_LastPos;
	Shader m_Shader;
	Camera* m_Camera = NULL;

	Timer m_Timer;
	Light m_Light;
	glm::mat4 m_ProjectionMatrix;
	bool m_Testing = false;

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

signals:
	void mouseClicked(glm::vec4 mouseRay, glm::vec3 cameraPos, glm::mat4 globalTransMat);
	void atomMoved(glm::vec3 direction);
};