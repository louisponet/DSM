#include <iostream>
#include <QtCore/Qt>
#include <glm/gtx/transform.hpp>
#include "../global.h"
#include "generator.h"
#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :QOpenGLWidget(parent), m_Shader("src/graphics/shaders/main.vert", "src/graphics/shaders/main.frag")
{
	QSurfaceFormat format;
	format.setDepthBufferSize(16);
	format.setVersion(4, 1);
	format.setRenderableType(QSurfaceFormat::OpenGL);
	setFormat(format);
	setFocusPolicy(Qt::StrongFocus);
// 	setMouseTracking(true);
}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{

	initializeOpenGLFunctions();
	Generator::instance()->init(this);
	const unsigned char* version = glGetString(GL_VERSION);
	std::cout << version << std::endl;
	m_Shader.load(this);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error: " << error << std::endl;
	}
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	m_ProjectionMatrix = glm::perspective(1.0472f/2.0f, (float)(this->width() / this->height()), 0.1f, 200.0f);
	m_Light.ambIntensity = 0.2f;
	m_Light.diffIntensity = 0.8f;
	m_Light.center = glm::vec3(0.0f, 0.0f, 100.0f);
	m_Light.focus = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Light.colour = glm::vec3(1.0f, 1.0f, 1.0f);
	m_Shader.enable();
	m_Shader.setSelectedIndex(selectedIndex);
 	m_Shader.setLightProperties(m_Light);
	m_Shader.disable();


}

void GLWidget::paintGL()
{
	
	makeCurrent();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (m_Camera!=NULL)
	{
		m_Shader.enable();
		glm::mat4& wtvMat = m_Camera->getWTVMat();
		m_Shader.setUniform3vec("eye_world_pos0", glm::vec3(glm::inverse(m_Camera->globalTransMat)*glm::vec4(m_Camera->position, 1.0f)));
		m_Shader.setUniform4mat("transformMatrix", m_ProjectionMatrix*wtvMat);
		if (!m_Testing)
		{
			if (m_SelectedStructure!=-1)
			{
				for (unsigned int i = 0; i < (*m_Vaos).size(); i++)
				{

					if ((*m_NumVerticesList)[i] == 0)
					{
						continue;
					}
					if (i == 1 | i == 2)
					{
						m_Shader.disableDiffuseLighting();
						m_Shader.setSelectedIndex(100000);

					}
					else
					{
						m_Shader.enableDiffuseLighting();
						m_Shader.setSelectedIndex(selectedIndex);
					}
					if (i == 3 & !showCell)
					{
						continue;
					}
					glBindVertexArray((*m_Vaos)[i]);
					GLenum error = glGetError();
					if (error != GL_NO_ERROR)
					{
						std::cout << "OpenGL Error: " << error << std::endl;
					}
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*m_IndBufs)[i]);
					glDrawElementsInstanced(GL_TRIANGLES, (*m_NumVerticesList)[i], GL_UNSIGNED_INT, 0, (*m_NumObjectsList)[i]);

				}
			}
		}
		else
		{
			m_Shader.enable();
			glBindVertexArray(m_Vao);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_IndBuf);
			glDrawElementsInstanced(GL_TRIANGLES, m_NumVertices , GL_UNSIGNED_INT, 0, m_NumObjects);
		}
		m_Shader.disable();
	}
	glBindVertexArray(0);
 	blockSignals(false);
}

void GLWidget::resizeGL(int w, int h)
{

	makeCurrent();
	m_ProjectionMatrix = glm::perspective(1.0472f / 2.0f,(float) w/h, 0.1f, 200.0f);
	update();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	float dx = event->x() - m_LastPos.x();
	float dy = event->y() - m_LastPos.y();
	if (event->buttons() & Qt::RightButton)
	{
		if (event->modifiers() & Qt::ControlModifier)
		{
			m_Camera->mouseUpdate(dx, dy);
		}
		else
		{
			m_Camera->rotateWorld(dx, dy);
		}
	}
	if (event->buttons()&Qt::LeftButton)
	{
		if (event->modifiers()&Qt::AltModifier)
		{
			if (selectedIndex!=100000)
			{

				float x = 2.0f*event->x() / this->width() - 1.0f;
				float y = 1.0f - 2.0f*event->y() / this->height();
				float x1 = 2.0f*m_LastPos.x() / this->width() - 1.0f;
				float y1 = 1.0f - 2.0f*m_LastPos.y() / this->height();
				Sphere& sphere = m_Structures[m_SelectedStructure]->spheres[selectedIndex];
				glm::vec3 coords = glm::vec3((m_Camera->globalTransMat)*glm::vec4(sphere.center,1.0f));
				float dist = glm::distance(m_Camera->position, coords);
				float dx1 = 19.5*(x - x1)*dist;
				float dy1 = 19.5*(y - y1)*dist;
				glm::vec4 vec = glm::inverse(glm::lookAt(m_Camera->position, m_Camera->position + m_Camera->viewDirection, m_Camera->up))*glm::inverse(m_ProjectionMatrix)*glm::vec4(dx1, dy1, 0.0f, 0.0f)*m_Camera->globalTransMat;

				emit atomMoved(glm::vec3(vec));
			}
		}
	}
	m_LastPos = event->pos();
	update();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	m_LastPos = event->pos();
	if (event->buttons()&Qt::LeftButton)
	{
		glm::vec4 pickedRay = calculateMouseRay(event->x(), event->y());
		emit mouseClicked(pickedRay, m_Camera->position, m_Camera->globalTransMat);

	}

}

void GLWidget::wheelEvent(QWheelEvent *event)
{
	if (event->buttons()&Qt::LeftButton)
	{
		if (event->modifiers()&Qt::AltModifier)
		{
			glm::vec4 mouseRay = calculateMouseRay(event->x(), event->y());
			emit atomMoved(glm::vec3(mouseRay*m_Camera->globalTransMat)*(float)(event->angleDelta().x())/10.0f);
		}
	}
	else
	{
		m_Camera->moveForward(event->angleDelta().y());
	}
	update();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
#if DEBUG
	std::cout << "keyPressEvent" << std::endl;
#endif
	if (event->key() == Qt::Key_Z)
	{
		
		if (event->modifiers() & Qt::AltModifier)
		{

			emit atomMoved(m_Camera->viewDirection);
		}
		else
		{
			m_Camera->moveForward();
		}
	}
	else if (event->key() == Qt::Key_Q)
	{
		if (event->modifiers()&Qt::AltModifier)
		{
			emit atomMoved(-m_Camera->strafeDirection);
		}
		else{ m_Camera->strafeLeft(); }
		
	}
	else if (event->key() == Qt::Key_D)
	{
		if (event->modifiers()&Qt::AltModifier)
		{
			emit atomMoved(m_Camera->strafeDirection);
		}
		else { m_Camera->strafeRight(); }
		
	}
	else if (event->key() == Qt::Key_S)
	{
		if (event->modifiers()&Qt::AltModifier)
		{
			emit atomMoved(-m_Camera->viewDirection);
		}
		else { m_Camera->moveBackward(); }
		
	}
	else if (event->key() == Qt::Key_R)
	{
		if (event->modifiers()&Qt::AltModifier)
		{
			emit atomMoved(m_Camera->up);
		}
		else { m_Camera->moveUp(); }
		
	}
	else if (event->key() == Qt::Key_F)
	{
		if (event->modifiers()&Qt::AltModifier)
		{
			emit atomMoved(-m_Camera->up);
		}
		else { m_Camera->moveDown(); }
	}
	update();
}


glm::vec4 GLWidget::calculateMouseRay(float x, float y)
{
	float x1 = 2.0f*x / this->width() - 1.0f;
	float y1 =  1.0f-2.0f*y / this ->height();
	return glm::normalize(glm::inverse(glm::lookAt(m_Camera->position,m_Camera->position+m_Camera->viewDirection,m_Camera->up))*glm::vec4(glm::vec2(glm::inverse(m_ProjectionMatrix)*glm::vec4(x1, y1, -1.0f, 1.0f)), -1.0f, 0.0f));

}

void GLWidget::updateSelectedAtom(unsigned int& selectedAtom)
{

	selectedIndex = selectedAtom;
	update();
}

void GLWidget::addStructure(Structure* structure)
{
	m_Structures.push_back(structure);
}

void GLWidget::removeStructure(int index)
{

	m_Structures.erase(m_Structures.begin() + index);
}

void GLWidget::selectStructure(int index)
{
	if (index == -1)
	{
		m_SelectedStructure = -1;

		return;
	}
	m_SelectedStructure = index;
	m_Vaos = &(m_Structures[index]->vaos);
	m_IndBufs = &(m_Structures[index]->indBufs);
	m_NumObjectsList =&( m_Structures[index]->numObjsList);
	m_NumVerticesList= &(m_Structures[index]->numVertsList);
	m_Camera = &m_Structures[index]->camera;

	update();
}


