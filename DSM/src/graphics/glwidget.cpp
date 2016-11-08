
#include <iostream>
#include <QtCore/Qt>
#include <glm/gtx/transform.hpp>
#include "../global.h"
#include "generator.h"
#include "glwidget.h"


GLWidget::GLWidget(QWidget *parent) :QOpenGLWidget(parent),
m_3DShader("src/graphics/shaders/main.vert","src/graphics/shaders/main.frag"),
m_2DShader("src/graphics/shaders/2D.vert","src/graphics/shaders/2D.frag"),
m_HUDShader("src/graphics/shaders/HUD.vert", "src/graphics/shaders/HUD.frag")
{

    QSurfaceFormat format;
	format.setDepthBufferSize(16);
	format.setVersion(4, 1);

	format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
	format.setSamples(4);
	setFormat(format);
	setFocusPolicy(Qt::StrongFocus);

// 	setMouseTracking(true);
}

GLWidget::~GLWidget()
{
	delete m_HUDvao;
}

void GLWidget::initializeGL()
{
    makeCurrent();
	initializeOpenGLFunctions();
	Generator::instance()->init(this);

	const unsigned char* version = glGetString(GL_VERSION);
	std::cout << version << std::endl;
	m_3DShader.load(this);
	m_2DShader.load(this);
	m_HUDShader.load(this);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
#ifdef _DEBUG
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error trying to render2D: " << error << std::endl;
	}
#endif
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	m_ProjectionMatrix = glm::perspective(1.0472f/2.0f, (float)(this->width() / this->height()), 0.1f, 200.0f);
	m_OrthogonalMatrix = glm::ortho(-1.0f*width()/height(), 1.0f*width() / height(), -1.0f, 1.0f);
	m_Light.ambIntensity = 0.2f;
	m_Light.diffIntensity = 0.8f;
	m_Light.center = glm::vec3(0.0f, 0.0f, 100.0f);
	m_Light.focus = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Light.colour = glm::vec3(1.0f, 1.0f, 1.0f);
	m_3DShader.enable();
	m_3DShader.initLocations();
	m_3DShader.setSelectedIndex(selectedIndex);
 	m_3DShader.setLightProperties(m_Light);
	m_3DShader.disable();
	m_2DShader.enable();
	m_2DShader.setLightProperties(m_Light);
	m_2DShader.disable();


	initHUD();


}

void GLWidget::initHUD()
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colours;
	m_HUDvao = new VAO();
	//delete these still in a way 
	VBO* vertVBO = new VBO(GL_ARRAY_BUFFER);
	VBO* colVBO  = new VBO(GL_ARRAY_BUFFER);

	Generator::instance()->createHUDRectangle(glm::vec3(-1.17f, -0.7f, -0.9f), glm::vec3(-1.17f, -1.0f, -0.9f), glm::vec3(0.1f), &vertices, &colours);
	m_HUDVertCount += 6;
	//Generator::instance()->createHUDRectangle(glm::vec3(-1.17f, -0.7f, -0.89f), glm::vec3(-1.17f, -0.1f, -0.89f), glm::vec3(1.0f), &vertices,&colours);
	m_HUDVertCount += 6;

	m_HUDvao->create();
	m_HUDvao->bind();
	
	vertVBO->create();
	colVBO->create();

	vertVBO->bind();
	vertVBO->allocateAndSubmit(&vertices[0][0], vertices.size() * sizeof(glm::vec3), GL_STATIC_DRAW);
	m_HUDvao->submitVBO(vertVBO, VAO::VERT);

	colVBO->bind();
	colVBO->allocateAndSubmit(&colours[0][0],colours.size() *sizeof(glm::vec3), GL_STATIC_DRAW);
	m_HUDvao->submitVBO(colVBO, VAO::COL);

	colVBO->unbind();
	m_HUDvao->unbind();


}

void GLWidget::paintGL()
{
	
	makeCurrent();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (m_Camera!=NULL)
	{
		
		render3D();
		renderHUD();
		render2D();	
		
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
	m_3DVaos = &(m_Structures[index]->vaos3D);
	m_3DIndBufs = &(m_Structures[index]->indBufs3D);
	m_3DNumObjectsList =&( m_Structures[index]->numObjsList3D);
	m_3DNumVerticesList= &(m_Structures[index]->numVertsList3D);
	m_2DVaos = &(m_Structures[index]->vaos2D);
	m_2DIndBufs = &(m_Structures[index]->indBufs2D);
	m_2DNumObjectsList = &(m_Structures[index]->numObjsList2D);
	m_2DNumVerticesList = &(m_Structures[index]->numVertsList2D);
	m_Camera = &m_Structures[index]->camera;

	update();
}

void GLWidget::submit2DVao(VAO* vao,VBO* indBuf,GLuint numIndices)
{
	(*m_2DVaos).push_back(vao);
	(*m_2DIndBufs).push_back(indBuf);
	(*m_2DNumVerticesList).push_back(numIndices);
	(*m_2DNumObjectsList).push_back(1);

}

void GLWidget::renderHUD()
{
	m_HUDShader.enable();
	m_HUDShader.setUniform4mat("transformMatrix", m_OrthogonalMatrix);
	m_HUDvao->bind();
	glDrawArrays(GL_TRIANGLES, 0, m_HUDVertCount);
	m_HUDShader.disable();
}

void GLWidget::render2D()
{
	
	m_2DShader.enable();
	m_2DShader.setUniform4mat("transformMatrix", m_OrthogonalMatrix*m_Camera->transMat2D);
	for (int i = 0; i < (*m_2DVaos).size(); i++)
	{
		(*m_2DVaos)[i]->bind();
		(*m_2DIndBufs)[i]->bind();
		glDrawElementsInstanced(GL_TRIANGLES, (*m_2DNumVerticesList)[i], GL_UNSIGNED_INT, 0, (*m_2DNumObjectsList)[i]);
	}
#ifdef _DEBUG
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error trying to render2D: " << error << std::endl;
	}
#endif
	m_2DShader.disable();

}

void GLWidget::render3D()
{
	m_3DShader.enable();

	glm::mat4 wtvMat = m_Camera->getWTVMat();
	m_3DShader.setUniform3vec("eye_world_pos0", glm::vec3(glm::inverse(m_Camera->globalTransMat)*glm::vec4(m_Camera->position, 1.0f)));
	m_3DShader.setUniform4mat("transformMatrix", m_ProjectionMatrix*wtvMat);
	if (m_SelectedStructure != -1)
	{
		for (unsigned int i = 0; i < (*m_3DVaos).size(); i++)
		{

			if ((*m_3DNumVerticesList)[i] == 0)
			{
				continue;
			}
			if (i == 1 | i == 2)
			{
				m_3DShader.setDiffuseLighting(0.4f);
				m_3DShader.setSelectedIndex(100000);

			}
			else
			{
				m_3DShader.enableDiffuseLighting();
				m_3DShader.setSelectedIndex(selectedIndex);
			}
			if (i == 3 & !showCell)
			{
				continue;
			}
			(*m_3DVaos)[i]->bind();
			(*m_3DIndBufs)[i]->bind();
			glDrawElementsInstanced(GL_TRIANGLES, (*m_3DNumVerticesList)[i], GL_UNSIGNED_INT, 0, (*m_3DNumObjectsList)[i]);
		}
	}
	m_3DShader.disable();
}