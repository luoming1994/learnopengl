#ifndef SHADER_FILE_H
#define SHADER_FILE_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
protected:
	GLuint mShaderId;

public:
	Shader(){}
	Shader(std::string vertexPath, std::string fragmentPath);
	~Shader() {}

	std::string ReadFile(std::string &path_name);
	GLuint CompileShaderFromFile(std::string &path, GLuint shader_type);
	GLuint LinkShaders(GLuint* shaders, int len, bool del_shader = true);

	// activate the shader
	bool GetShaderId() { return mShaderId; }
	void UseShader();
	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, GLint value) const;
	void SetFloat(const std::string &name, GLfloat value) const;
	void Set3Float(const std::string &name, GLfloat v1, GLfloat v2, GLfloat v3) const;
	void Set4Float(const std::string &name, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4) const;
	void Set3FloatVector(const std::string &name, GLfloat *vs) const;
	void Set4FloatVector(const std::string &name, GLfloat *vs) const;
	void SetMat4Float(const std::string &name, glm::mat4 &transform) const;
	void SetTextureIndex(const std::string &name, int index) const;

private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void PrintCompileErrors(GLuint shader, GLenum type);
};
#endif