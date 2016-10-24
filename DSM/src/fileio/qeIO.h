#pragma once
#include "../entities/particle.h"
#include "../entities/structure.h"
class qeRW
{
public:
	qeRW();
	~qeRW();


	bool loadIN(QString& path, std::vector <Particle> &out_atoms, glm::dmat3 &out_cell);
	bool saveStructure(Structure* structure,bool saveAs =false);
private:

};
