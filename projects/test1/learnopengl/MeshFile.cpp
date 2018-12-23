#include "MeshFile.h"



Mesh::Mesh() 
	: mVAO(0)
	, mVBO(0)
	, mEBO(0)
	, mVertexNum(0)
{
}


Mesh::~Mesh()
{
	if (mVAO) glDeleteVertexArrays(1, &mVAO);
	if (mVBO) glDeleteBuffers(1, &mVBO);
	if (mEBO) glDeleteBuffers(1, &mEBO);
}

Mesh::Mesh(float *vertices,int vLen, unsigned int *indices, int iLen)
	: mVAO(0)
	, mVBO(0)
	, mEBO(0)
	, mVertexNum(iLen)
{
	LoadVertices(vertices, vLen);
	LoadIndices(indices, iLen);
}

Mesh::Mesh(float *vertices, int vLen)
	: mVAO(0)
	, mVBO(0)
	, mEBO(0)
	, mVertexNum(vLen)
{
	LoadVertices(vertices, vLen);
}

bool Mesh::LoadVertices(float *vertices, int len)
{
	//unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*vertices)*len, vertices, GL_STATIC_DRAW);
	return true;
}

bool Mesh::LoadIndices(unsigned int *indices, int len)
{
	glGenBuffers(1, &mEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*indices)*len, indices, GL_STATIC_DRAW);
	return true;
}

//	设置定点属性
//	sizes 一个顶点每种数据类型占用的长度数组
void Mesh::SetVerticesAttribute(GLint *sizes, int len)
{
	GLsizei stride = 0;		//	一个顶点到下一个顶点的数据偏移
	for (int i = 0; i < len; i++)
		stride += sizes[i];
	int pointer = 0;
	glBindVertexArray(mVAO);
	for (int i = 0; i < len; i++)
	{
		glVertexAttribPointer(i, sizes[i], GL_FLOAT, GL_FALSE, stride* sizeof(float), (void*)(pointer * sizeof(float)));
		glEnableVertexAttribArray(i);
		pointer += sizes[i];
	}
	if (mEBO == 0)
		mVertexNum = mVertexNum / stride;
}

void Mesh::UseMesh()
{
	
	glBindVertexArray(mVAO);
	if (mEBO)
	{
		glDrawElements(GL_TRIANGLES, mVertexNum, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, mVertexNum);
	}
	
}
