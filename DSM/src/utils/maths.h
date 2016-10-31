#pragma once
#define PI 3.14159265358979f
#include <glm/glm.hpp>
struct maths {

	static glm::mat4 scaleCM( glm::vec3 v)
	{
		glm::mat4 scaleMat(1.0f);
		scaleMat[0][0] = 1.0f*v[0];
	
		scaleMat[1][1] = 1.0f*v[1];
		scaleMat[2][2] = 1.0f*v[2];
		return scaleMat;
	}
	static glm::mat4 rotateCM(glm::mat4 baseMat, float a,glm::vec3 rotAx)
	{
		glm::mat4 rotMat;
		float u = rotAx[0];
		float v = rotAx[1];
		float w = rotAx[2];

		rotMat[0][0] = pow(u, 2) + (1 - pow(u, 2))*cos(a);
		rotMat[0][1] = u*v*(1 - cos(a)) + w*sin(a);
		rotMat[0][2] = u*w*(1 - cos(a)) - v*sin(a);
		rotMat[0][3] = 0.0f;
		rotMat[1][0] = u*v*(1 - cos(a)) - w*sin(a);
		rotMat[1][1] = pow(v, 2) + (1 - pow(v, 2))*cos(a);
		rotMat[1][2] = v*w*(1 - cos(a)) + u*sin(a);
		rotMat[1][3] = 0.0f;
		rotMat[2][0] = u*w*(1 - cos(a)) + v*sin(a);
		rotMat[2][1] = v*w*(1 - cos(a)) - u*sin(a);
		rotMat[2][2] = pow(w, 2) + (1 - pow(w, 2))*cos(a);
		rotMat[2][3] = 0.0f;
		rotMat[3][0] = 0.0f;
		rotMat[3][1] = 0.0f;
		rotMat[3][2] = 0.0f;
		rotMat[3][3] = 1.0f;
		return rotMat*baseMat;
	}

	static glm::mat4 translateCM(glm::mat4 baseMat,  glm::vec3 transVec)
	{
		glm::mat4 transMat;
		transMat[0][0] = 1.0f;
		transMat[0][1] = 0.0f;
		transMat[0][2] = 0.0f;
		transMat[0][3] = 0.0f;
		transMat[1][0] = 0.0f;
		transMat[1][1] = 1.0f;
		transMat[1][2] = 0.0f;
		transMat[1][3] = 0.0f;
		transMat[2][0] = 0.0f;
		transMat[2][1] = 0.0f;
		transMat[2][2] = 1.0f;
		transMat[2][3] = 0.0f;
		transMat[3][0] = transVec[0];
		transMat[3][1] = transVec[1];
		transMat[3][2] = transVec[2];
		transMat[3][3] = 1.0f;
		return transMat*baseMat;
	}

	static glm::mat4 translateCM(  glm::vec3 transVec)
	{
		glm::mat4 transMat;
		transMat[0][0] = 1.0f;
		transMat[0][1] = 0.0f;
		transMat[0][2] = 0.0f;
		transMat[0][3] = 0.0f;
		transMat[1][0] = 0.0f;
		transMat[1][1] = 1.0f;
		transMat[1][2] = 0.0f;
		transMat[1][3] = 0.0f;
		transMat[2][0] = 0.0f;
		transMat[2][1] = 0.0f;
		transMat[2][2] = 1.0f;
		transMat[2][3] = 0.0f;
		transMat[3][0] = transVec[0];
		transMat[3][1] = transVec[1];
		transMat[3][2] = transVec[2];
		transMat[3][3] = 1.0f;
		return transMat;
	}

	static glm::mat4 lookatCM(glm::mat4 baseMat,  glm::vec3 eye,  glm::vec3 center,  glm::vec3 up)
	{
		glm::mat4 lookAtMat;
		glm::vec3 z = glm::normalize(eye - center);
		glm::vec3 y = up;
		glm::vec3 x = glm::cross(y, z);
		y = glm::cross(z, x);

		lookAtMat[0][0] = x[0];
		lookAtMat[0][1] = y[0];
		lookAtMat[0][2] = z[0];
		lookAtMat[0][3] = 0.0f;
		lookAtMat[1][0] = x[1];
		lookAtMat[1][1] = y[1];
		lookAtMat[1][2] = z[1];
		lookAtMat[1][3] = 0.0f;
		lookAtMat[2][0] = x[2];
		lookAtMat[2][1] = y[2];
		lookAtMat[2][2] = z[2];
		lookAtMat[2][3] = 0.0f;
		lookAtMat[3][0] = -glm::dot(x, eye);
		lookAtMat[3][1] = -glm::dot(y, eye);
		lookAtMat[3][2] = -glm::dot(z, eye);
		lookAtMat[3][3] = 1.0f;
		return lookAtMat*baseMat;

 	}
};