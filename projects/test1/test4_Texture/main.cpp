#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "TextureFile.h"
#include "../learnopengl/MeshFile.h"
#include "../learnopengl/Utils.h"
#include "../learnopengl/ShaderFile.h"




std::string TEXTURE_1_PATH = "../resources/textures/container.jpg";
std::string TEXTURE_2_PATH = "../resources/textures/awesomeface.png";
//std::string TEXTURE_2_PATH = "../resources/textures/awesomeface.jpg";
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
std::string TITLE = "OpenGL";

int main()
{
	InitGlew();

	GLFWwindow* window = CreateGlewWindow(SCR_WIDTH, SCR_HEIGHT, TITLE, framebuffer_size_callback);
	if (window == NULL)	return -1;
	if (!LoadGlad())	return -1;

	
	Shader ourShader("./shader_texture.vs", "./shader_texture.ps");

	
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};


	Mesh mesh(vertices,sizeof(vertices)/sizeof(*vertices), 
		indices, sizeof(indices) / sizeof(*indices));
	GLint locations[3] = { 3,3,2 };	// positions=3、colors=3、texture coords=2
	mesh.SetVerticesAttribute(locations, sizeof(locations) / sizeof(*locations));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// load and create a texture 
	// -------------------------
	Texture texture1(TEXTURE_1_PATH,true);
	Texture texture2(TEXTURE_2_PATH);
	// load and create a texture 
	// -------------------------
	


	// 设置texture的sampler
	// -------------------------------------------------------------------------------------------
	ourShader.UseShader(); // 设置uniforms需要先激活Shader
	ourShader.SetInt("texture1", 0);
	ourShader.SetInt("texture2", 1);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// bind textures on corresponding texture units
		texture1.UseTexture(0);
		texture2.UseTexture(1);
		//std::cout << texture1.GetTextureId() << texture2.GetTextureId();
		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);*/

		// render container
		ourShader.UseShader();
		mesh.UseMesh();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	CloseGlew();
	return 0;
}
