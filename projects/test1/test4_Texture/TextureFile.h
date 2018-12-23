#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Texture
{
protected:
	GLuint mTextureId;

public:
	Texture();
	virtual ~Texture();
	Texture(std::string &file_path, bool flip_y = false);

	GLuint Load2DTexture(std::string &path_name, bool flip_y=false);
	GLuint GetTextureId();
	void UseTexture(GLuint texture_index);
};

