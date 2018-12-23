#include "ShaderFile.h"


Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
	GLuint vShader = CompileShaderFromFile(vertexPath, GL_VERTEX_SHADER);
	GLuint pShader = CompileShaderFromFile(fragmentPath, GL_FRAGMENT_SHADER);
	GLuint shaders[2] = { vShader , pShader };
	mShaderId = LinkShaders(shaders, 2);
}

std::string Shader::ReadFile(std::string &path_name)
{
	std::ifstream file;
	std::string code = "";
	// 确保抛出异常:
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file.open(path_name);
		std::stringstream steam;
		steam << file.rdbuf();
		file.close();
		code = steam.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Load File " << path_name << "Fail!" << std::endl;
	}
	return code;
}

void Shader::PrintCompileErrors(GLuint shader, GLenum type)
{
	int success;
	char infoLog[1024];
	if (type == GL_COMPILE_STATUS)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: "
				<< type << "\n" << infoLog
				<< "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else if (type == GL_LINK_STATUS)
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: "
				<< type << "\n" << infoLog
				<< "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

GLuint Shader::CompileShaderFromFile(std::string &path, GLuint shader_type)
{
	if (!(shader_type == GL_VERTEX_SHADER || shader_type == GL_FRAGMENT_SHADER))
	{
		std::cout << "Input shader_type error(Must be GL_VERTEX_SHADER or GL_FRAGMENT_SHADER)";
		return 0;
	}
		
	std::string code = ReadFile(path);
	const char* str_code = code.c_str();
	GLuint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &str_code, NULL);
	glCompileShader(shader);
	PrintCompileErrors(shader, GL_COMPILE_STATUS);

	return shader;
}

GLuint Shader::LinkShaders(GLuint* shaders, int len, bool del_shader)
{
	// link shaders
	GLuint shaderProgram = glCreateProgram();
	for (int i = 0; i < len; i++)
		glAttachShader(shaderProgram, shaders[i]);
	glLinkProgram(shaderProgram);
	PrintCompileErrors(shaderProgram, GL_LINK_STATUS);
	if (del_shader)
		for (int i = 0; i < len; i++)
			glDeleteShader(shaders[i]);

	return shaderProgram;
}

// activate the shader
void Shader::UseShader()
{
	glUseProgram(mShaderId);
}

void Shader::SetBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(mShaderId, name.c_str()), (GLint)value);
}

void Shader::SetInt(const std::string &name, GLint value) const
{
	glUniform1i(glGetUniformLocation(mShaderId, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, GLfloat value) const
{
	glUniform1f(glGetUniformLocation(mShaderId, name.c_str()), value);
}

void Shader::Set3Float(const std::string &name, GLfloat v1, GLfloat v2, GLfloat v3) const
{
	GLint location = glGetUniformLocation(mShaderId, name.c_str());
	glUniform3f(location, v1, v2, v3);
}

void Shader::Set4Float(const std::string &name, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4 ) const
{
	GLint location = glGetUniformLocation(mShaderId, name.c_str());
	glUniform4f(location, v1, v2, v3, v4);
}

void Shader::Set3FloatVector(const std::string &name, GLfloat *vs) const
{
	GLint location = glGetUniformLocation(mShaderId, name.c_str());
	GLsizei count = 3;
	glUniform3fv(location, count, vs);
}

void Shader::Set4FloatVector(const std::string &name, GLfloat *vs) const
{
	GLint location = glGetUniformLocation(mShaderId, name.c_str());
	GLsizei count = 4;
	glUniform3fv(location, count, vs);
}




