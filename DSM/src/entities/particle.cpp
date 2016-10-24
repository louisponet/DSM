#include "particle.h"


Particle::Particle(const elements::Element& element, glm::dvec3 coords)
	:element(element),coords(coords)
{
}

Particle::~Particle()
{
}

std::string& Particle::getName()
{
	return element.Name;
}

std::string& Particle::getSymbol()
{
	return element.Symbol;
}


float Particle::getWeight()
{
	return element.Atomic_Weight;
}

float Particle::getCova()
{
	return element.Covalent_Radius / 100;
}

glm::vec3& Particle::getColour()
{
	return element.Colour;
}

void Particle::setCoords(const glm::dvec3& coords1)
{
	coords = coords1;
}
