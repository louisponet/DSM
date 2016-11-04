#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif
#include "objreader.h"
#include <fstream>
#include <algorithm>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	GLuint position_ID;
	GLuint normal_ID;

	Vertex(glm::vec3 pos, glm::vec3 norm, GLuint pos_ID, GLuint norm_ID) :position(pos), normal(norm), position_ID(pos_ID), normal_ID(norm_ID) {};
};

struct Face
{
	Vertex vert1;
	Vertex vert2;
	Vertex vert3;
};


objReader::objReader()
{
}


objReader::~objReader()
{
}

bool objReader::loadOBJ(const char* path, std::vector<glm::vec3>&out_vertices, std::vector<GLuint>&out_indices, std::vector<glm::vec3>&out_normals)
{
	std::vector< GLuint > vertexIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec3 > temp_normals;

#ifdef __APPLE__
		CFURLRef appUrlRef;
        appUrlRef = CFBundleCopyResourceURL(CFBundleGetMainBundle(),CFStringCreateWithCString(NULL,path,kCFStringEncodingMacRoman),NULL,NULL);
	    CFStringRef filePathRef = CFURLCopyPath(appUrlRef);
	    const char* pathString = CFStringGetCStringPtr(filePathRef,kCFStringEncodingUTF8);
#else
	   const char* pathString = path;
#endif
	FILE *file = fopen(pathString, "r");
	if (file == NULL)
	{
		printf("Impossible to open the file! \n");
		return false;
	}

	while (1) {
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) { break; }

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			out_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2;
			GLuint vertexIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
			if (matches != 6) {
				printf("File can't be read by our parser!\n");
				return false;
			}
		
			out_indices.push_back(vertexIndex[0]-1);
			out_indices.push_back(vertexIndex[1]-1);
			out_indices.push_back(vertexIndex[2]-1);
			normalIndices.push_back(normalIndex[0]-1);
			normalIndices.push_back(normalIndex[1]-1);
			normalIndices.push_back(normalIndex[2]-1);
		}
	}
	out_normals.resize(temp_normals.size());
	for (unsigned int i = 0; i < normalIndices.size();i++) {
		GLuint Index = out_indices[i];
		out_normals[Index] = temp_normals[normalIndices[i]];
	}

#ifdef __APPLE__
	    CFRelease(appUrlRef);
	    CFRelease(filePathRef);
#endif

	return true;
}

bool objReader::loadOBJ1(const char* path, std::vector<glm::vec3>&out_vertices, std::vector<GLuint>&out_indices, std::vector<glm::vec3>&out_normals)
{
	std::vector< GLuint > vertexIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec3 > temp_normals;
	std::vector<Vertex>vertexData;
	std::vector<Face> faces;
#ifdef __APPLE__
		CFURLRef appUrlRef;
        appUrlRef = CFBundleCopyResourceURL(CFBundleGetMainBundle(),CFStringCreateWithCString(NULL,path,kCFStringEncodingMacRoman),NULL,NULL);
	    CFStringRef filePathRef = CFURLCopyPath(appUrlRef);
	    const char* pathString = CFStringGetCStringPtr(filePathRef,kCFStringEncodingUTF8);
#else
	   const char* pathString = path;
#endif
	FILE *file = fopen(pathString, "r");
	if (file == NULL)
	{
		printf("Impossible to open the file! \n");
		return false;
	}

	while (1) {
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) { break; }

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2;
			GLuint vertexIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
			if (matches != 6) {
				printf("File can't be read by our parser!\n");
				return false;
			}
			Vertex vert1 (temp_vertices[vertexIndex[0]-1],temp_normals[normalIndex[0]-1],vertexIndex[0]-1,normalIndex[0]-1);
			Vertex vert2 (temp_vertices[vertexIndex[1]-1],temp_normals[normalIndex[1]-1],vertexIndex[1]-1,normalIndex[1]-1);
			Vertex vert3 (temp_vertices[vertexIndex[2]-1],temp_normals[normalIndex[2]-1],vertexIndex[2]-1,normalIndex[2]-1);
			vertexData.push_back(vert1);
			vertexData.push_back(vert2);
			vertexData.push_back(vert3);
			Face face = { vert1,vert2,vert3 };
			faces.push_back(face);
		}
	}
	for (int i = vertexData.size() - 1; i >= 0; i--)
	{
		for (int i1 = 0; i1 < i; i1++)
		{
			if (vertexData[i].normal == vertexData[i1].normal&vertexData[i].position == vertexData[i1].position )
			{
				vertexData.erase(vertexData.begin() + i);
				break;
			}
		}
	}
	out_vertices.clear();
	out_normals.clear();
	out_indices.clear();
	for (int i = 0; i < vertexData.size(); i++)
	{
		out_vertices.push_back(vertexData[i].position);
		out_normals.push_back(vertexData[i].normal);
	}

	for (int i = 0; i < faces.size(); i++)
	{
		for (int i1 = 0; i1 < out_vertices.size(); i1++)
		{
			if (out_normals[i1] == faces[i].vert1.normal & out_vertices[i1] == faces[i].vert1.position)
			{
				out_indices.push_back(i1);
			}
		}
		for (int i1 = 0; i1 < out_vertices.size(); i1++)
		{
			if (out_normals[i1] == faces[i].vert2.normal & out_vertices[i1] == faces[i].vert2.position)
			{
				out_indices.push_back(i1);
			}
		}
		for (int i1 = 0; i1 < out_vertices.size(); i1++)
		{
			if (out_normals[i1] == faces[i].vert3.normal & out_vertices[i1] == faces[i].vert3.position)
			{
				out_indices.push_back(i1);
			}
		}
	}
#ifdef __APPLE__
	    CFRelease(appUrlRef);
	    CFRelease(filePathRef);
#endif

	return true;
}

