#pragma once
#include "particle.h"
#include <glm/glm.hpp>

class Bond
{
public:
	Bond(Particle& at1, Particle& at2, glm::vec3& colour) :atom1(at1), atom2(at2), colour(colour) {};
	Bond(const Bond& bond) :atom1(bond.atom1), atom2(bond.atom2), colour(bond.colour) {};
	
	Particle atom1, atom2;
    glm::vec3 colour;
};
