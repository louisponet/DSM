#pragma once

#include "particle.h"
#include "../renderables/sphere.h"
#include "../renderables/cylinder.h"
#include "../renderables/Cube.h"
#include "bond.h"
#include "../graphics/camera.h"

class Structure
{
private:

	std::vector<Particle> m_Atoms,m_SurroundingAtoms;
	std::vector<Bond> m_Bonds;
	bool m_Created = false;
	glm::dmat3 m_Cell = glm::dmat3(1.0f);
	glm::vec3 m_Origin;


public:
	std::vector<Cylinder> cylinders;
	std::vector<Sphere> spheres;
	std::vector<Cube> cubes;
	std::vector<glm::mat4> imMats;
	std::vector<GLuint> vertBufs, indBufs, normBufs, colBufs, matBufs, intBufs, powBufs, numberBufs,vaos;
	std::vector<unsigned int> numVertsList, numObjsList;
	Camera camera;
	unsigned int v1PosImCount = 0;
	unsigned int v1NegImCount = 0;
	unsigned int v2PosImCount = 0;
	unsigned int v2NegImCount = 0;
	unsigned int v3PosImCount = 0;
	unsigned int v3NegImCount = 0;
	bool displayCells = true;
	bool edited = false;
	bool isnew = false;
	QString file = NULL;
	QString name;
private:
	void calculateOrigin();
	void genSurroundings();
	void regenSurroundings(unsigned int& index);
	void genSpheres();
	void genBonds();
	void genFullCell();
	void regenBonds(unsigned int& index,glm::dvec3& oldCoords);
public:
	Structure();
	~Structure();
	std::vector<Particle>& getAtoms() { return m_Atoms; };
	glm::dmat3& getCell() { return m_Cell; };
	std::vector<Bond> &getBonds() { return m_Bonds; };
	glm::vec3& getOrigin() { return m_Origin; };
	
	void populateAtoms(std::vector<Particle> &inAtoms);
	void setCell(glm::dmat3& cell);
	void setCellCoords(uint& index, glm::dvec3 coords);
	std::vector<glm::dvec3> getAtomCoords();
	std::vector<glm::dvec3> getRelativeAtomCoords();
	std::vector<glm::vec3> getAtomColours();
	std::vector<std::string> getAtomSymbols();
	std::vector<float> getAtomRadii();
	void updateImageMats();
	void resetBufs();
	void updateAtomCoords(uint& index, glm::dvec3& addCoords);
	void setAtomCoords(uint& index1,glm::dvec3 coords);
	void addAtom(Particle atom);
	void removeAtom(int index);
	void create();

};