#define LINE_WIDTH 0.02f
#define LINE_COLOUR glm::vec3(10.0f,10.0f,10.0f)
#define CYLINDER_INT 0.0f
#define CYLINDER_POW 1.0f
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/transform.hpp>
#include "structure.h"
#include "../graphics/generator.h"
#include "../utils/maths.h"
#include "../utils/timer.h"

#ifdef _DEBUG
#include <iostream>
#endif

Structure::Structure()
{
}

Structure::~Structure()
{
	for (int i = 0; i < 3; i++)
	{
		vaos3D[i]->bind();
		vaos3D[i]->del();
		vaos3D[i]->unbind();
		delete vaos3D[i];
		vertBufs3D[i]->bind();
		vertBufs3D[i]->del();
		delete vertBufs3D[i];
		colBufs3D[i]->bind();
		colBufs3D[i]->del();
		delete colBufs3D[i];
		normBufs3D[i]->bind();
		normBufs3D[i]->del();
		delete normBufs3D[i];
		matBufs3D[i]->bind();
		matBufs3D[i]->del();
		delete matBufs3D[i];
		intBufs3D[i]->bind();
		intBufs3D[i]->del();
		delete intBufs3D[i];
		powBufs3D[i]->bind();
		powBufs3D[i]->del();
		delete powBufs3D[i];
		indBufs3D[i]->bind();
		indBufs3D[i]->del();
		delete indBufs3D[i];
	}
	numberBufs3D[0]->bind();
	numberBufs3D[0]->del();
	numberBufs3D[0]->unbind();
	delete numberBufs3D[0];

	for (int i = 0; i < 7; i++)
	{
		vaos2D[i]->bind();
		vaos2D[i]->del();
		vaos2D[i]->unbind();
		delete vaos2D[i];
		vertBufs2D[i]->bind();
		vertBufs2D[i]->del();
		delete vertBufs2D[i];
		colBufs2D[i]->bind();
		colBufs2D[i]->del();
		delete colBufs2D[i];
		normBufs2D[i]->bind();
		normBufs2D[i]->del();
		delete normBufs2D[i];
		matBufs2D[i]->bind();
		matBufs2D[i]->del();
		delete matBufs2D[i];
		intBufs2D[i]->bind();
		intBufs2D[i]->del();
		delete intBufs2D[i];
		powBufs2D[i]->bind();
		powBufs2D[i]->del();
		delete powBufs2D[i];
		indBufs2D[i]->bind();
		indBufs2D[i]->del();
		delete indBufs2D[i];
	}
}

//------------------All external modifier commands----------------------//

void Structure::populateAtoms(std::vector<Particle>& inAtoms)
{
	m_Atoms = inAtoms;
	calculateOrigin();
	genSpheres();
	genSurroundings();
	genBonds();
	Generator::instance()->initStructureBufs(this);
	Generator::instance()->genVaos(this);
	Generator::instance()->setupStructureCoordinateSystem(this);
}

void Structure::updateImageMats()
{
	std::vector<glm::mat4> v1TranslMats, v2TranslMats, v3TranslMats;
	v1TranslMats.reserve(v1PosImCount + v1NegImCount);
	v2TranslMats.reserve(v2PosImCount + v2NegImCount);
	v3TranslMats.reserve(v3PosImCount + v3NegImCount);
	imMats.clear();
	imMats.reserve((v1PosImCount + v1NegImCount)*(v2PosImCount + v2NegImCount)*(v3PosImCount + v3NegImCount));
	for (unsigned int i = 1; i <= v1PosImCount; i++)
	{
		v1TranslMats.push_back(maths::translateCM((glm::vec3)m_Cell[0] * (float)i));
	}
	for (unsigned int i = 1; i <= v1NegImCount; i++)
	{
		v1TranslMats.push_back(maths::translateCM((glm::vec3)m_Cell[0] * -(float)i));
	}
	for (unsigned int i = 1; i <= v2PosImCount; i++)
	{
		v2TranslMats.push_back(maths::translateCM((glm::vec3)m_Cell[1] * (float)i));
	}
	for (unsigned int i = 1; i <= v2NegImCount; i++)
	{
		v2TranslMats.push_back(maths::translateCM((glm::vec3)m_Cell[1] * -(float)i));
	}
	for (unsigned int i = 1; i <= v3PosImCount; i++)
	{
		v3TranslMats.push_back(maths::translateCM((glm::vec3)m_Cell[2] * (float)i));
	}
	for (unsigned int i = 1; i <= v3NegImCount; i++)
	{
		v3TranslMats.push_back(maths::translateCM((glm::vec3) m_Cell[2] * -(float)i));
	}

	for (unsigned int i = 0; i < v1TranslMats.size(); i++)
	{
		imMats.push_back(v1TranslMats[i]);
	}

	for (unsigned int i = 0; i < v2TranslMats.size(); i++)
	{
		imMats.push_back(v2TranslMats[i]);
		for (unsigned int i1 = 0; i1 < v1TranslMats.size(); i1++)
		{
			imMats.push_back(v1TranslMats[i1] * v2TranslMats[i]);
		}
	}

	for (unsigned int i = 0; i < v3TranslMats.size(); i++)
	{
		imMats.push_back(v3TranslMats[i]);
		for (unsigned int i1 = 0; i1 < v2TranslMats.size(); i1++)
		{
			imMats.push_back(v2TranslMats[i1] * v3TranslMats[i]);
			for (unsigned i2 = 0; i2 < v1TranslMats.size(); i2++)
			{
				imMats.push_back(v1TranslMats[i2] * v2TranslMats[i1] * v3TranslMats[i]);
			}
		}
		for (unsigned int i1 = 0; i1 < v1TranslMats.size(); i1++)
		{
			imMats.push_back(v1TranslMats[i1] * v3TranslMats[i]);
		}
	}

	Generator::instance()->regenStructureBufs(this);
	Generator::instance()->genVaos(this);

}

void Structure::updateAtomCoords(uint& index, glm::dvec3 new_coords)
{

    new_coords = glm::inverse(m_Cell)*new_coords;
	glm::dvec3 oldCoords = m_Atoms[index].coords;
    if(new_coords[0]>1.0f)
        new_coords[0]=1.0f;
    if(new_coords[1]>1.0f)
        new_coords[1]=1.0f;
    if(new_coords[2]>1.0f)
        new_coords[2]=1.0f;
    if(new_coords[0]<0.0f)
        new_coords[0]=0.0f;
    if(new_coords[1]<0.0f)
        new_coords[1]=0.0f;
    if(new_coords[2]<0.0f)
        new_coords[2]=0.0f;
    m_Atoms[index].coords = m_Cell*new_coords;
    spheres[index] = Sphere((glm::vec3) m_Atoms[index].coords, m_Atoms[index].getCova() * m_AtomScale, m_Atoms[index].getColour(), 0.9f, 10.0f, spheres[index].index);
	regenBonds(index, oldCoords);
	edited = true;
	Generator::instance()->updateStructureBufs(this);

}

void Structure::create()
{
	genFullCell();
	genSurroundings();
	genBonds();
	genSpheres();
	calculateOrigin();
	Generator::instance()->initStructureBufs(this);
	Generator::instance()->genVaos(this);
	Generator::instance()->setupStructureCoordinateSystem(this);

}




void Structure::setCell(glm::dmat3& cell)
{
	m_Cell = cell;
	genFullCell();
}

void Structure::setCellCoords(uint& index, glm::dvec3 coords)
{
	m_Cell[index] = coords;
}

void Structure::setAtomCoords(uint& index1, glm::dvec3 coords)
{
	m_Atoms[index1].coords = coords;
}

void Structure::addAtom(Particle atom)
{
	m_Atoms.push_back(atom);
}

void Structure::removeAtom(int index)
{
	m_Atoms.erase(m_Atoms.begin() + index);
}

//------------------All internal generating commands----------------------//

void Structure::genSpheres()
{
	spheres.clear();
	spheres.reserve(m_Atoms.size());
	unsigned int indexCounter = 0;
	for (unsigned int i = 0; i < m_Atoms.size(); i++)
	{
        spheres.push_back(Sphere((glm::vec3)m_Atoms[i].coords, m_Atoms[i].getCova() * m_AtomScale, m_Atoms[i].getColour(), 0.9f, 32.0f, indexCounter));
		indexCounter += 1;
	}
}



void Structure::calculateOrigin()
{
    float totX=0, totY=0, totZ=0, meanX, meanY, meanZ;
    for (uint i = 0 ; i< m_Atoms.size();i++)
    {
        totX += m_Atoms[i].coords.x;
		totY += m_Atoms[i].coords.y;
		totZ += m_Atoms[i].coords.z;
	}
	meanX = totX / m_Atoms.size();
	meanY = totY / m_Atoms.size();
	meanZ = totZ / m_Atoms.size();
	m_Origin = glm::vec3(meanX, meanY, meanZ);
	camera.structureOrigin = m_Origin;
#ifdef _DEBUG
	std::cout << "Structure Origin: x="<< m_Origin.x << " y=" <<m_Origin.y<< " z="<< m_Origin.z << std::endl;
#endif
}

void Structure::genFullCell()
{
	cubes.clear();
	cubes.reserve(12);
	std::vector<glm::vec3> cellCoords;
	cellCoords.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	for (unsigned int i=0; i < 3; i++)
	{
		cellCoords.push_back(glm::column(m_Cell, i));
	}
	cellCoords.push_back(glm::vec3(m_Cell[0][0] + m_Cell[1][0], m_Cell[0][1] + m_Cell[1][1], m_Cell[0][2] + m_Cell[1][2]));
	cellCoords.push_back(glm::vec3(m_Cell[0][0] + m_Cell[2][0], m_Cell[0][1] + m_Cell[2][1], m_Cell[0][2] + m_Cell[2][2]));
	cellCoords.push_back(glm::vec3(m_Cell[1][0] + m_Cell[2][0], m_Cell[1][1] + m_Cell[2][1], m_Cell[1][2] + m_Cell[2][2]));
	cellCoords.push_back(glm::vec3(m_Cell[0][0] + m_Cell[1][0]+ m_Cell[2][0],  m_Cell[0][1]+ m_Cell[1][1] + m_Cell[2][1], m_Cell[0][2] + m_Cell[1][2] + m_Cell[2][2]));

	cubes.push_back(Cube(cellCoords[0], cellCoords[1], LINE_WIDTH, LINE_COLOUR));
	cubes.push_back(Cube(cellCoords[0], cellCoords[2], LINE_WIDTH, LINE_COLOUR));
	cubes.push_back(Cube(cellCoords[4], cellCoords[2], LINE_WIDTH, LINE_COLOUR));
	cubes.push_back(Cube(cellCoords[4], cellCoords[1], LINE_WIDTH, LINE_COLOUR));
	cubes.push_back(Cube(cellCoords[0], cellCoords[3], LINE_WIDTH, LINE_COLOUR));
	cubes.push_back(Cube(cellCoords[1], cellCoords[5], LINE_WIDTH, LINE_COLOUR));
	cubes.push_back(Cube(cellCoords[4], cellCoords[7], LINE_WIDTH, LINE_COLOUR));
	cubes.push_back(Cube(cellCoords[2], cellCoords[6], LINE_WIDTH, LINE_COLOUR));
	cubes.push_back(Cube(cellCoords[6], cellCoords[3], LINE_WIDTH, LINE_COLOUR));
	cubes.push_back(Cube(cellCoords[6], cellCoords[7], LINE_WIDTH, LINE_COLOUR));
	cubes.push_back(Cube(cellCoords[7], cellCoords[5], LINE_WIDTH, LINE_COLOUR));
	cubes.push_back(Cube(cellCoords[3], cellCoords[5], LINE_WIDTH, LINE_COLOUR));


}

void Structure::genSurroundings()
{
	m_SurroundingAtoms.clear();
	m_SurroundingAtoms.reserve(26 * m_Atoms.size());
    for(uint i = 0; i < m_Atoms.size();i++)
	{
		m_SurroundingAtoms.push_back(Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x + m_Cell[0][0], m_Atoms[i].coords.y + m_Cell[0][1],
			m_Atoms[i].coords.z + m_Cell[0][2])));
		m_SurroundingAtoms.push_back(Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x + m_Cell[1][0], m_Atoms[i].coords.y + m_Cell[1][1],
			m_Atoms[i].coords.z + m_Cell[1][2])));
		m_SurroundingAtoms.push_back(Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x + m_Cell[2][0], m_Atoms[i].coords.y + m_Cell[2][1],
			m_Atoms[i].coords.z + m_Cell[2][2])));
		m_SurroundingAtoms.push_back(Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x - m_Cell[0][0], m_Atoms[i].coords.y - m_Cell[0][1],
			m_Atoms[i].coords.z - m_Cell[0][2])));
		m_SurroundingAtoms.push_back(Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x - m_Cell[1][0], m_Atoms[i].coords.y - m_Cell[1][1],
			m_Atoms[i].coords.z - m_Cell[1][2])));
		m_SurroundingAtoms.push_back(Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x - m_Cell[2][0], m_Atoms[i].coords.y - m_Cell[2][1],
			m_Atoms[i].coords.z - m_Cell[2][2])));
		m_SurroundingAtoms.push_back(Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x + m_Cell[0][0] + m_Cell[1][0],
			m_Atoms[i].coords.y + m_Cell[0][1] + m_Cell[1][1],
			m_Atoms[i].coords.z + m_Cell[0][2] + m_Cell[1][2])));
		m_SurroundingAtoms.push_back(Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x + m_Cell[0][0] - m_Cell[1][0],
			m_Atoms[i].coords.y + m_Cell[0][1] - m_Cell[1][1],
			m_Atoms[i].coords.z + m_Cell[0][2] - m_Cell[1][2])));
		m_SurroundingAtoms.push_back(Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x - m_Cell[0][0] + m_Cell[1][0],
			m_Atoms[i].coords.y - m_Cell[0][1] + m_Cell[1][1],
			m_Atoms[i].coords.z - m_Cell[0][2] + m_Cell[1][2])));
		m_SurroundingAtoms.push_back(Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x - m_Cell[0][0] - m_Cell[1][0],
			m_Atoms[i].coords.y - m_Cell[0][1] - m_Cell[1][1],
			m_Atoms[i].coords.z - m_Cell[0][2] - m_Cell[1][2])));
		m_SurroundingAtoms.push_back(Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x + m_Cell[0][0] + m_Cell[2][0],
			m_Atoms[i].coords.y + m_Cell[0][1] + m_Cell[2][1],
			m_Atoms[i].coords.z + m_Cell[0][2] + m_Cell[2][2])));
		m_SurroundingAtoms.push_back(Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x + m_Cell[0][0] - m_Cell[2][0],
			m_Atoms[i].coords.y + m_Cell[0][1] - m_Cell[2][1],
			m_Atoms[i].coords.z + m_Cell[0][2] - m_Cell[2][2])));
		m_SurroundingAtoms.push_back(Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x - m_Cell[0][0] + m_Cell[2][0],
			m_Atoms[i].coords.y - m_Cell[0][1] + m_Cell[2][1],
			m_Atoms[i].coords.z - m_Cell[0][2] + m_Cell[2][2])));
		m_SurroundingAtoms.push_back(Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x - m_Cell[0][0] - m_Cell[2][0],
			m_Atoms[i].coords.y - m_Cell[0][1] - m_Cell[2][1],
			m_Atoms[i].coords.z - m_Cell[0][2] - m_Cell[2][2])));
		m_SurroundingAtoms.push_back(Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x + m_Cell[1][0] + m_Cell[2][0],
			m_Atoms[i].coords.y + m_Cell[1][1] + m_Cell[2][1],
			m_Atoms[i].coords.z + m_Cell[1][2] + m_Cell[2][2])));
		m_SurroundingAtoms.push_back(Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x + m_Cell[1][0] - m_Cell[2][0],
			m_Atoms[i].coords.y + m_Cell[1][1] - m_Cell[2][1],
			m_Atoms[i].coords.z + m_Cell[1][2] - m_Cell[2][2])));
		m_SurroundingAtoms.push_back(Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x - m_Cell[1][0] + m_Cell[2][0],
			m_Atoms[i].coords.y - m_Cell[1][1] + m_Cell[2][1],
			m_Atoms[i].coords.z - m_Cell[1][2] + m_Cell[2][2])));
		m_SurroundingAtoms.push_back(Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x - m_Cell[1][0] - m_Cell[2][0],
			m_Atoms[i].coords.y - m_Cell[1][1] - m_Cell[2][1],
			m_Atoms[i].coords.z - m_Cell[1][2] - m_Cell[2][2])));


		m_SurroundingAtoms.push_back(Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x + m_Cell[0][0] + m_Cell[1][0] + m_Cell[2][0],
			m_Atoms[i].coords.y + m_Cell[0][1] + m_Cell[1][1] + m_Cell[2][1],
			m_Atoms[i].coords.z + m_Cell[0][2] + m_Cell[1][2] + m_Cell[2][2])));
		m_SurroundingAtoms.push_back(
			Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x + m_Cell[0][0] - m_Cell[1][0] + m_Cell[2][0],
				m_Atoms[i].coords.y + m_Cell[0][1] - m_Cell[1][1] + m_Cell[2][1],
				m_Atoms[i].coords.z + m_Cell[0][2] - m_Cell[1][2] + m_Cell[2][2])));
		m_SurroundingAtoms.push_back(
			Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x + m_Cell[0][0] + m_Cell[1][0] - m_Cell[2][0],
				m_Atoms[i].coords.y + m_Cell[0][1] + m_Cell[1][1] - m_Cell[2][1],
				m_Atoms[i].coords.z + m_Cell[0][2] + m_Cell[1][2] - m_Cell[2][2])));
		m_SurroundingAtoms.push_back(
			Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x - m_Cell[0][0] + m_Cell[1][0] + m_Cell[2][0],
				m_Atoms[i].coords.y - m_Cell[0][1] + m_Cell[1][1] + m_Cell[2][1],
				m_Atoms[i].coords.z - m_Cell[0][2] + m_Cell[1][2] + m_Cell[2][2])));
		m_SurroundingAtoms.push_back(
			Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x + m_Cell[0][0] - m_Cell[1][0] - m_Cell[2][0],
				m_Atoms[i].coords.y + m_Cell[0][1] - m_Cell[1][1] - m_Cell[2][1],
				m_Atoms[i].coords.z + m_Cell[0][2] - m_Cell[1][2] - m_Cell[2][2])));
		m_SurroundingAtoms.push_back(
			Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x - m_Cell[0][0] + m_Cell[1][0] - m_Cell[2][0],
				m_Atoms[i].coords.y - m_Cell[0][1] + m_Cell[1][1] - m_Cell[2][1],
				m_Atoms[i].coords.z - m_Cell[0][2] + m_Cell[1][2] - m_Cell[2][2])));
		m_SurroundingAtoms.push_back(
			Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x - m_Cell[0][0] - m_Cell[1][0] + m_Cell[2][0],
				m_Atoms[i].coords.y - m_Cell[0][1] - m_Cell[1][1] + m_Cell[2][1],
				m_Atoms[i].coords.z - m_Cell[0][2] - m_Cell[1][2] + m_Cell[2][2])));
		m_SurroundingAtoms.push_back(
			Particle(m_Atoms[i].getElement(), glm::vec3(m_Atoms[i].coords.x - m_Cell[0][0] - m_Cell[1][0] - m_Cell[2][0],
				m_Atoms[i].coords.y - m_Cell[0][1] - m_Cell[1][1] - m_Cell[2][1],
				m_Atoms[i].coords.z - m_Cell[0][2] - m_Cell[1][2] - m_Cell[2][2])));
	}
#ifdef _DEBUG
		std::cout << "Done populating surrounding atoms.\n Size is:" << m_SurroundingAtoms.size() << std::endl;
#endif
}

void Structure::regenSurroundings(unsigned int& index)
{
	uint stride = m_SurroundingAtoms.size() / m_Atoms.size();
	uint start = index*stride;
	m_SurroundingAtoms[start].coords = glm::vec3(m_Atoms[index].coords.x + m_Cell[0][0], m_Atoms[index].coords.y + m_Cell[0][1],
		m_Atoms[index].coords.z + m_Cell[0][2]);
	m_SurroundingAtoms[start+1].coords = glm::vec3(m_Atoms[index].coords.x + m_Cell[1][0], m_Atoms[index].coords.y + m_Cell[1][1],
		m_Atoms[index].coords.z + m_Cell[1][2]);
	m_SurroundingAtoms[start+2].coords = glm::vec3(m_Atoms[index].coords.x + m_Cell[2][0], m_Atoms[index].coords.y + m_Cell[2][1],
		m_Atoms[index].coords.z + m_Cell[2][2]);
	m_SurroundingAtoms[start+3].coords = glm::vec3(m_Atoms[index].coords.x - m_Cell[0][0], m_Atoms[index].coords.y - m_Cell[0][1],
		m_Atoms[index].coords.z - m_Cell[0][2]);						 										 
	m_SurroundingAtoms[start+4].coords = glm::vec3(m_Atoms[index].coords.x - m_Cell[1][0], m_Atoms[index].coords.y - m_Cell[1][1],
		m_Atoms[index].coords.z - m_Cell[1][2]);						 										 
	m_SurroundingAtoms[start+5].coords = glm::vec3(m_Atoms[index].coords.x - m_Cell[2][0], m_Atoms[index].coords.y - m_Cell[2][1],
		m_Atoms[index].coords.z - m_Cell[2][2]);

	m_SurroundingAtoms[start+6].coords = glm::vec3(m_Atoms[index].coords.x + m_Cell[0][0] + m_Cell[1][0],
		m_Atoms[index].coords.y + m_Cell[0][1] + m_Cell[1][1],
		m_Atoms[index].coords.z + m_Cell[0][2] + m_Cell[1][2]);
	m_SurroundingAtoms[start+7].coords = glm::vec3(m_Atoms[index].coords.x + m_Cell[0][0] - m_Cell[1][0],
		m_Atoms[index].coords.y + m_Cell[0][1] - m_Cell[1][1],
		m_Atoms[index].coords.z + m_Cell[0][2] - m_Cell[1][2]);
	m_SurroundingAtoms[start+8].coords = glm::vec3(m_Atoms[index].coords.x - m_Cell[0][0] + m_Cell[1][0],
		m_Atoms[index].coords.y - m_Cell[0][1] + m_Cell[1][1],
		m_Atoms[index].coords.z - m_Cell[0][2] + m_Cell[1][2]);
	m_SurroundingAtoms[start+9].coords = glm::vec3(m_Atoms[index].coords.x - m_Cell[0][0] - m_Cell[1][0],
		m_Atoms[index].coords.y - m_Cell[0][1] - m_Cell[1][1],
		m_Atoms[index].coords.z - m_Cell[0][2] - m_Cell[1][2]);
	m_SurroundingAtoms[start+10].coords = glm::vec3(m_Atoms[index].coords.x + m_Cell[0][0] + m_Cell[2][0],
		m_Atoms[index].coords.y + m_Cell[0][1] + m_Cell[2][1],
		m_Atoms[index].coords.z + m_Cell[0][2] + m_Cell[2][2]);
	m_SurroundingAtoms[start+11].coords = glm::vec3(m_Atoms[index].coords.x + m_Cell[0][0] - m_Cell[2][0],
		m_Atoms[index].coords.y + m_Cell[0][1] - m_Cell[2][1],
		m_Atoms[index].coords.z + m_Cell[0][2] - m_Cell[2][2]);
	m_SurroundingAtoms[start+12].coords = glm::vec3(m_Atoms[index].coords.x - m_Cell[0][0] + m_Cell[2][0],
		m_Atoms[index].coords.y - m_Cell[0][1] + m_Cell[2][1],
		m_Atoms[index].coords.z - m_Cell[0][2] + m_Cell[2][2]);
	m_SurroundingAtoms[start+13].coords = glm::vec3(m_Atoms[index].coords.x - m_Cell[0][0] - m_Cell[2][0],
		m_Atoms[index].coords.y - m_Cell[0][1] - m_Cell[2][1],
		m_Atoms[index].coords.z - m_Cell[0][2] - m_Cell[2][2]);
	m_SurroundingAtoms[start+14].coords = glm::vec3(m_Atoms[index].coords.x + m_Cell[1][0] + m_Cell[2][0],
		m_Atoms[index].coords.y + m_Cell[1][1] + m_Cell[2][1],
		m_Atoms[index].coords.z + m_Cell[1][2] + m_Cell[2][2]);
	m_SurroundingAtoms[start+15].coords = glm::vec3(m_Atoms[index].coords.x + m_Cell[1][0] - m_Cell[2][0],
		m_Atoms[index].coords.y + m_Cell[1][1] - m_Cell[2][1],
		m_Atoms[index].coords.z + m_Cell[1][2] - m_Cell[2][2]);
	m_SurroundingAtoms[start+16].coords = glm::vec3(m_Atoms[index].coords.x - m_Cell[1][0] + m_Cell[2][0],
		m_Atoms[index].coords.y - m_Cell[1][1] + m_Cell[2][1],
		m_Atoms[index].coords.z - m_Cell[1][2] + m_Cell[2][2]);
	m_SurroundingAtoms[start+17].coords = glm::vec3(m_Atoms[index].coords.x - m_Cell[1][0] - m_Cell[2][0],
		m_Atoms[index].coords.y - m_Cell[1][1] - m_Cell[2][1],
		m_Atoms[index].coords.z - m_Cell[1][2] - m_Cell[2][2]);

	m_SurroundingAtoms[start+18].coords = glm::vec3(m_Atoms[index].coords.x + m_Cell[0][0] + m_Cell[1][0] + m_Cell[2][0],
		m_Atoms[index].coords.y + m_Cell[0][1] + m_Cell[1][1] + m_Cell[2][1],
		m_Atoms[index].coords.z + m_Cell[0][2] + m_Cell[1][2] + m_Cell[2][2]);
	m_SurroundingAtoms[start+19].coords = glm::vec3(m_Atoms[index].coords.x + m_Cell[0][0] - m_Cell[1][0] + m_Cell[2][0],
		m_Atoms[index].coords.y + m_Cell[0][1] - m_Cell[1][1] + m_Cell[2][1],
		m_Atoms[index].coords.z + m_Cell[0][2] - m_Cell[1][2] + m_Cell[2][2]);
	m_SurroundingAtoms[start+20].coords = glm::vec3(m_Atoms[index].coords.x + m_Cell[0][0] + m_Cell[1][0] - m_Cell[2][0],
		m_Atoms[index].coords.y + m_Cell[0][1] + m_Cell[1][1] - m_Cell[2][1],
		m_Atoms[index].coords.z + m_Cell[0][2] + m_Cell[1][2] - m_Cell[2][2]);
	m_SurroundingAtoms[start+21].coords = glm::vec3(m_Atoms[index].coords.x - m_Cell[0][0] + m_Cell[1][0] + m_Cell[2][0],
		m_Atoms[index].coords.y - m_Cell[0][1] + m_Cell[1][1] + m_Cell[2][1],
		m_Atoms[index].coords.z - m_Cell[0][2] + m_Cell[1][2] + m_Cell[2][2]);
	m_SurroundingAtoms[start+22].coords = glm::vec3(m_Atoms[index].coords.x + m_Cell[0][0] - m_Cell[1][0] - m_Cell[2][0],
		m_Atoms[index].coords.y + m_Cell[0][1] - m_Cell[1][1] - m_Cell[2][1],
		m_Atoms[index].coords.z + m_Cell[0][2] - m_Cell[1][2] - m_Cell[2][2]);
	m_SurroundingAtoms[start+23].coords = glm::vec3(m_Atoms[index].coords.x - m_Cell[0][0] + m_Cell[1][0] - m_Cell[2][0],
		m_Atoms[index].coords.y - m_Cell[0][1] + m_Cell[1][1] - m_Cell[2][1],
		m_Atoms[index].coords.z - m_Cell[0][2] + m_Cell[1][2] - m_Cell[2][2]);
	m_SurroundingAtoms[start+24].coords = glm::vec3(m_Atoms[index].coords.x - m_Cell[0][0] - m_Cell[1][0] + m_Cell[2][0],
		m_Atoms[index].coords.y - m_Cell[0][1] - m_Cell[1][1] + m_Cell[2][1],
		m_Atoms[index].coords.z - m_Cell[0][2] - m_Cell[1][2] + m_Cell[2][2]);
	m_SurroundingAtoms[start+25].coords = glm::vec3(m_Atoms[index].coords.x - m_Cell[0][0] - m_Cell[1][0] - m_Cell[2][0],
		m_Atoms[index].coords.y - m_Cell[0][1] - m_Cell[1][1] - m_Cell[2][1],
		m_Atoms[index].coords.z - m_Cell[0][2] - m_Cell[1][2] - m_Cell[2][2]);
}

void Structure::genBonds()
{

	using namespace glm;
	m_Bonds.clear();
	cylinders.clear();
	

	for (unsigned int i=0; i < m_Atoms.size(); i++)
	{
		Particle& atom1= m_Atoms[i];
		dvec3& pos1 = atom1.coords;
		float cov1 = atom1.getCova();
		for (unsigned int i2 = i + 1; i2 < m_Atoms.size(); i2++)
		{
			Particle& atom2 = m_Atoms[i2];
			dvec3& pos2 = atom2.coords;
			float cov2 = atom2.getCova();
			float dist = glm::distance(pos1, pos2);
            if (cov1*m_CovaScale + cov2*m_CovaScale> dist )
			{
				m_Bonds.push_back(Bond(atom1, atom2, atom1.getColour()));
				m_Bonds.push_back(Bond(atom2, atom1, atom2.getColour()));
				
			}
		}
		for (unsigned int i2 = 0; i2 < m_SurroundingAtoms.size(); i2++)
		{
			Particle& atom2 = m_SurroundingAtoms[i2];
			dvec3& pos2 = atom2.coords;
			float cov2 = atom2.getCova();
			float dist = glm::distance(pos1, pos2);
            if (cov1*m_CovaScale + cov2*m_CovaScale> dist )
			{
				m_Bonds.push_back(Bond(atom1, atom2, atom1.getColour()));
			}
		}
	}
	cylinders.reserve(m_Bonds.size());
	for (unsigned int i = 0; i < m_Bonds.size(); i++)
	{
		Particle& atom1=m_Bonds[i].atom1, &atom2=m_Bonds[i].atom2;
        cylinders.push_back(Cylinder((glm::vec3)atom1.coords, (glm::vec3) atom2.coords, m_BondScale, atom1.getColour(), CYLINDER_INT, 1.0f, Cylinder::STRUCTURE));
	}


}

void Structure::regenBonds(unsigned int& index, glm::dvec3& oldCoords)
{
	Particle& atom1 = m_Atoms[index];
	uint stride = m_SurroundingAtoms.size() / m_Atoms.size();
	uint start = index*stride;
	for (int i = m_Bonds.size()-1; i>=0;i--)
	{
		if (m_Bonds[i].atom1.coords == oldCoords| m_Bonds[i].atom2.coords == oldCoords)
		{
			m_Bonds.erase(m_Bonds.begin() + i);
			cylinders.erase(cylinders.begin() + i);
			continue;
		}
		for (uint i1 = start;i1<start+stride;i1++)
		{
			if (m_Bonds[i].atom2.coords == m_SurroundingAtoms[i1].coords)
			{
				m_Bonds.erase(m_Bonds.begin() + i);
				cylinders.erase(cylinders.begin() + i);
				break;
			}
		}
	}
	regenSurroundings(index);
	glm::dvec3& pos1 = atom1.coords;
	float cov1 = atom1.getCova();
	for (unsigned int i2 = 0; i2 < m_Atoms.size(); i2++)
	{
		if (i2==index)
		{
			continue;
		}
		Particle& atom2 = m_Atoms[i2];
		glm::dvec3& pos2 = atom2.coords;
		float cov2 = atom2.getCova();
		float dist = glm::distance(pos1, pos2);
        if (cov1*m_CovaScale + cov2*m_CovaScale> dist )
		{
			m_Bonds.push_back(Bond(atom1, atom2, atom1.getColour()));
			m_Bonds.push_back(Bond(atom2, atom1, atom2.getColour()));

            cylinders.push_back(Cylinder((glm::vec3) atom1.coords,(glm::vec3) atom2.coords, m_BondScale, atom1.getColour(), CYLINDER_INT, 1.0f, Cylinder::STRUCTURE));
            cylinders.push_back(Cylinder((glm::vec3) atom2.coords,(glm::vec3) atom1.coords, m_BondScale, atom2.getColour(), CYLINDER_INT, 1.0f, Cylinder::STRUCTURE));

		}
	}
	for (unsigned int i2 = 0; i2 < m_SurroundingAtoms.size(); i2++)
	{
		Particle& atom2 = m_SurroundingAtoms[i2];
		glm::dvec3& pos2 = atom2.coords;
		float cov2 = atom2.getCova();
		float dist = glm::distance(pos1, pos2);
        if (cov1*m_CovaScale + cov2*m_CovaScale> dist )
        {
			m_Bonds.push_back(Bond(atom1, atom2, atom1.getColour()));
            cylinders.push_back(Cylinder((glm::vec3) atom1.coords, (glm::vec3) atom2.coords, m_BondScale, atom1.getColour(), CYLINDER_INT, 1.0f, Cylinder::STRUCTURE));
		}
	}
	for (unsigned int i = start; i< start+stride; i++)
	{
		Particle& atom2 = m_SurroundingAtoms[i];
		glm::dvec3& pos2 = atom2.coords;
		float cov2 = atom2.getCova();
		for (uint i2 = 0 ; i2<m_Atoms.size();i2++)
		{
			Particle& atom1 = m_Atoms[i2];
			glm::dvec3& pos1 = atom1.coords;
			float cov1 = atom1.getCova();
			float dist = glm::distance(pos1, pos2);
            if (cov1*m_CovaScale + cov2*m_CovaScale> dist )
			{
				m_Bonds.push_back(Bond(atom1, atom2, atom1.getColour()));
                cylinders.push_back(Cylinder((glm::vec3) atom1.coords, (glm::vec3) atom2.coords, m_BondScale, atom1.getColour(), CYLINDER_INT, 1.0f,Cylinder::STRUCTURE));
			}
		}
	}
}

//------------------All external extraction commands----------------------//

std::vector<glm::dvec3> Structure::getAtomCoords()
{
	std::vector<glm::dvec3> atomCoords;
    for (uint i = 0 ; i<m_Atoms.size();i++)
	{
		atomCoords.push_back(m_Atoms[i].coords);
	}
	return atomCoords;
}

std::vector < glm::dvec3> Structure::getRelativeAtomCoords()
{
	std::vector<glm::dvec3> atomCoords;
	for (uint i =0 ; i< m_Atoms.size();i++)
	{
		atomCoords.push_back(glm::inverse(m_Cell)*m_Atoms[i].coords);
	}
	return atomCoords;
}

std::vector<glm::vec3> Structure::getAtomColours()
{
	std::vector<glm::vec3> atomColors;
    for (uint i = 0 ; i<m_Atoms.size();i++)
	{
		atomColors.push_back(m_Atoms[i].getColour());
	}
	return atomColors;
}

std::vector<std::string> Structure::getAtomSymbols()
{
	std::vector<std::string> atomSymbols;
    for(uint i = 0; i<m_Atoms.size();i++)
	{
		atomSymbols.push_back(m_Atoms[i].getSymbol());
	}
	return atomSymbols;
}

std::vector<float> Structure::getAtomRadii()
{
	std::vector<float> atomRadii;
    for (uint i = 0 ; i < m_Atoms.size();i++)
	{
		atomRadii.push_back(m_Atoms[i].getCova());
	}
	return atomRadii;
}

float Structure::getCovaScale() const
{
    return m_CovaScale;
}

void Structure::setCovaScale(float CovaScale)
{
    m_CovaScale = CovaScale;
    genBonds();

    Generator::instance()->deleteCylinderBufs(this);
    Generator::instance()->setupCylinderBufs(this);
}

float Structure::getAtomScale() const
{
    return m_AtomScale;
}

void Structure::setAtomScale(float AtomScale)
{
    m_AtomScale = AtomScale;
    genSpheres();
    Generator::instance()->updateStructureBufs(this);
}

float Structure::getBondScale() const
{
    return m_BondScale;
}

void Structure::setBondScale(float BondScale)
{
    m_BondScale = BondScale;
    genBonds();
    Generator::instance()->updateStructureBufs(this);
}

//-----------------Reset commands---------------------------------//

void Structure::resetBufs3D()
{
	Generator::instance()->deleteStructureBuffers(this);
	vaos3D.clear();
	colBufs3D.clear();
	vertBufs3D.clear();
	matBufs3D.clear();
	numberBufs3D.clear();
	intBufs3D.clear();
	powBufs3D.clear();
	normBufs3D.clear();
	indBufs3D.clear();
}

