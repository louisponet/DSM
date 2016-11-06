#pragma once
#include <glm/glm.hpp>

class Camera
	
{

public:
	Camera();
	~Camera();
	
	glm::vec3 position;
	glm::vec3 viewDirection;
	glm::vec3 up;
	glm::vec3 strafeDirection;
	glm::vec3 structureOrigin;
	glm::mat4 globalTransMat;
	glm::mat4 transMat2D;
	glm::mat4 inverseGlobalMat;
	float MOVEMENT_SPEED = 1.0f;

	void mouseUpdate(const float& dx, const float& dy);
	void rotateWorld(const float& dx, const float& dy);
	glm::mat4 getWTVMat() ;
	glm::mat4 getWTVMat(glm::mat4& matrix) ;

	void moveForward();
	void moveForward(const float& delta);
	void moveBackward();
	void strafeLeft();
	void strafeRight();
	void moveUp();
	void moveDown();
	void focusX();
	void focusY();
	void focusZ();
	

};