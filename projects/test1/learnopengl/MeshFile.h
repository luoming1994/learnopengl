#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
class Mesh
{
protected:
	GLuint mVAO;
	GLuint mVBO;
	GLuint mEBO;
	GLsizei mVertexNum;

public:
	Mesh();
	Mesh(float *vertices, int vLen);
	Mesh(float *vertices, int vLen, unsigned int *indices, int iLen);
	~Mesh();

	bool LoadVertices(float *vertices, int len);
	bool LoadIndices(unsigned int *indices, int len);
	void SetVerticesAttribute(GLint *sizes, int len);

	void UseMesh();
};

