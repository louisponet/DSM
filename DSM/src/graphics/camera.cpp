#include "camera.h"
#include "../utils/maths.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
	position = glm::vec3(0.0f, -50.0f, 10.0f);
	viewDirection = glm::vec3(0.0f, 1.0f, 0.0f);
	strafeDirection = glm::vec3(1.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 0.0f, 1.0f);
	structureOrigin = glm::vec3(0.0f, 0.0f, 0.0f);
	globalTransMat = glm::mat4();
	transMat2D = glm::mat4();
	inverseGlobalMat = glm::mat4();

}

Camera::~Camera()
{

}

glm::mat4 Camera::getWTVMat()
{
	return maths::lookatCM(globalTransMat, position, position + viewDirection, up);
}

glm::mat4 Camera::getWTVMat(glm::mat4& matrix) 
{
	return maths::lookatCM(globalTransMat,position, position+viewDirection, up)*matrix;
}

void Camera::mouseUpdate(const float& dx, const float& dy)
{

	glm::mat4 totMat = glm::rotate(glm::rotate(glm::mat4(), -dy / 500.0f, strafeDirection), -dx / 500.0f, up);
	viewDirection = glm::normalize(glm::vec3(totMat*glm::vec4(viewDirection, 0.0f)));
	up = glm::normalize(glm::vec3(totMat*glm::vec4(up, 0.0f)));
	strafeDirection = glm::normalize(glm::vec3(totMat*glm::vec4(strafeDirection, 0.0f)));

}

void Camera::rotateWorld(const float& dx, const float& dy)
{
	globalTransMat = maths::translateCM(maths::rotateCM(maths::rotateCM(maths::translateCM(globalTransMat, -structureOrigin), dy / 80.0f, strafeDirection), dx / 80.0f, up), +structureOrigin);
	transMat2D = maths::translateCM(maths::rotateCM(maths::rotateCM(maths::translateCM(transMat2D, -glm::vec3(-1.2f, -0.8f, 0.0f)), -dy / 80.0f, glm::vec3(-1.0f, 0.0f, 0.0f)), dx / 80.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(-1.2f, -0.8f, 0.0f));
}

void Camera::moveForward()
{
	position += MOVEMENT_SPEED*viewDirection;
}

void Camera::moveForward(const float& delta)
{
	position += MOVEMENT_SPEED*viewDirection*delta/40.0f;
}

void Camera::moveBackward()
{
	position -= MOVEMENT_SPEED*viewDirection;
}

void Camera::strafeLeft()
{
	position -= MOVEMENT_SPEED*strafeDirection;
}

void Camera::strafeRight()
{
	position += MOVEMENT_SPEED*strafeDirection;
}

void Camera::moveUp()
{
	position += MOVEMENT_SPEED*up;
}

void Camera::moveDown()
{
	position -= MOVEMENT_SPEED*up;
}

void Camera::focusX()
{
	position = glm::vec3(-20.0f, 0.0f, 10.0f);
	viewDirection = glm::vec3(1.0f, 0.0f, 0.0f);
	strafeDirection = glm::vec3(0.0f, -1.0f, 0.0f);
	up = glm::vec3(0.0f, 0.0f, 1.0f);
	globalTransMat = glm::mat4();
}

void Camera::focusY()
{
	position = glm::vec3(0.0f, -20.0f, 10.0f);
	viewDirection = glm::vec3(0.0f, 1.0f, 0.0f);
	strafeDirection = glm::vec3(1.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 0.0f, 1.0f);
	globalTransMat = glm::mat4();
}

void Camera::focusZ()
{
	position = glm::vec3(0.0f, 0.0f, 40.0f);
	viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	strafeDirection = glm::vec3(1.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	globalTransMat = glm::mat4();
}