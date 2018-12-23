#include "TextureFile.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


Texture::Texture()
{
}


Texture::~Texture()
{
}

Texture::Texture(std::string &path_name, bool flip_y)
{
	Load2DTexture(path_name);
}

GLuint Texture::Load2DTexture(std::string &path_name, bool flip_y)
{
	// load and create a texture 

	//GLuint mTextureId;

	glGenTextures(1, &mTextureId);
	glBindTexture(GL_TEXTURE_2D, mTextureId);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	if (flip_y)
		stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load(path_name.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		//std::cout << "width " << width << " height " << height<< " channels " << nrChannels << std::endl;
		if (nrChannels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else if (nrChannels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			std::cout << "iamge's channel is " << nrChannels<< "is not supported !"<< std::endl;
		}

		glGenerateMipmap(GL_TEXTURE_2D);
		//std::cout << data << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	return mTextureId;
}

GLuint Texture::GetTextureId()
{
	return mTextureId;
}

void Texture::UseTexture(GLuint texture_index)
{
	if (texture_index > (GL_TEXTURE31 - GL_TEXTURE0))
		std::cout << "texture_index is too Large; No more than " << GL_TEXTURE31 - GL_TEXTURE0 << std::endl;
	glActiveTexture(GL_TEXTURE0 + texture_index);
	//std::cout << ((GL_TEXTURE0 + texture_index) == GL_TEXTURE0) << ((GL_TEXTURE0 + texture_index) == GL_TEXTURE1) << std::endl;
	glBindTexture(GL_TEXTURE_2D, mTextureId);
}