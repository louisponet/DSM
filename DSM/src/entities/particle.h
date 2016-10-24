#pragma once
#include "elements.h"
#include "glm/glm.hpp"
#include <string>

class Particle
{

private:
	elements::Element element;
public:
	glm::dvec3 coords;
public:
	Particle( const elements::Element& element, glm::dvec3 coords);
	~Particle();
	elements::Element& getElement() { return element; };
	std::string& getName();
	std::string& getSymbol();
	float getWeight();
	float getCova();
	glm::vec3& getColour();
	void setCoords(const glm::dvec3& coords1);

};