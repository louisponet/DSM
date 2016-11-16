#pragma once

#include "particle.h"
#include "../renderables/sphere.h"
#include "../renderables/cylinder.h"
#include "../renderables/Cube.h"
#include "bond.h"
#include "../graphics/camera.h"
#include "../graphics/VBO.h"
#include "../graphics/VAO.h"


class Structure
{
private:

	std::vector<Particle> m_Atoms,m_SurroundingAtoms;
	std::vector<Bond> m_Bonds;
	bool m_Created = false;
	glm::dmat3 m_Cell = glm::dmat3(1.0f);
	glm::vec3 m_Origin;
    float m_CovaScale = 1.2f;
    float m_AtomScale = 0.5f;
    float m_BondScale = 0.2f;


public:
	struct Properties
	{
		bool edited = false;
		bool cellEdited = false;
		bool isnew = false;
	};

	struct Options
	{
		bool displayCells = true;
	};
	Properties properties;
	Options options;

	std::vector<Cylinder> cylinders;
	std::vector<Sphere> spheres;
	std::vector<Cube> cubes;
	std::vector<glm::mat4> imMats;
	std::vector<VBO*> vertBufs3D, normBufs3D, colBufs3D, matBufs3D, intBufs3D, powBufs3D, numberBufs3D;
	std::vector<VBO*> vertBufs2D, normBufs2D, colBufs2D, matBufs2D, intBufs2D, powBufs2D, numberBufs2D;
	std::vector<VBO*> indBufs3D,indBufs2D;
	std::vector<VAO*> vaos3D;
	std::vector<VAO*> vaos2D;
	std::vector<unsigned int> numVertsList3D, numObjsList3D;
	std::vector<unsigned int> numVertsList2D, numObjsList2D;


	Camera camera;
	unsigned int v1PosImCount = 0;
	unsigned int v1NegImCount = 0;
	unsigned int v2PosImCount = 0;
	unsigned int v2NegImCount = 0;
	unsigned int v3PosImCount = 0;
	unsigned int v3NegImCount = 0;
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
	void resetBufs3D();
	void updateAtomCoords(uint& index, glm::dvec3 addCoords);
	void setAtomCoords(uint& index1,glm::dvec3 coords);
	void addAtom(Particle atom);
	void removeAtom(int index);

	void create();

    float getCovaScale() const;
    void setCovaScale(float CovaScale);
    float getAtomScale() const;
    void setAtomScale(float AtomScale);
    float getBondScale() const;
    void setBondScale(float BondScale);
};
