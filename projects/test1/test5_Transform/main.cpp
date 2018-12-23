#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../learnopengl/Utils.h"
#include "../learnopengl/MeshFile.h"
#include "../learnopengl/ShaderFile.h"
#include "../learnopengl/TextureFile.h"


std::string TEXTURE_1_PATH = "../resources/textures/container.jpg";
std::string TEXTURE_2_PATH = "../resources/textures/awesomeface.png";
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
std::string TITLE = "OpenGL";

int main()
{
	InitGlew();

	GLFWwindow* window = CreateGlewWindow(SCR_WIDTH, SCR_HEIGHT, TITLE, framebuffer_size_callback);
	if (window == NULL)	return -1;
	if (!LoadGlad())	return -1;

	Shader ourShader("./shader_transform.vs", "./shader_transform.ps");

	float vertices[] = {
		// positions          // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	//	Mesh数据
	Mesh mesh(vertices, sizeof(vertices) / sizeof(*vertices),
		indices, sizeof(indices) / sizeof(*indices));
	GLint locations[2] = { 3,2 };	// positions=3、texture coords=2
	mesh.SetVerticesAttribute(locations, sizeof(locations) / sizeof(*locations));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// 纹理
	Texture texture1(TEXTURE_1_PATH,true);
	Texture texture2(TEXTURE_2_PATH);

	// 设置texture的sampler
	ourShader.UseShader(); // 设置uniforms需要先激活Shader
	ourShader.SetInt("texture1", 0);
	ourShader.SetInt("texture2", 1);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		texture1.UseTexture(0);
		texture2.UseTexture(1);

		// 变换
		glm::mat4 transform;
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		
		ourShader.UseShader();
		ourShader.SetMat4Float("transform", transform);
		//unsigned int transformLoc = glGetUniformLocation(ourShader.GetShaderId(), "transform");
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		mesh.UseMesh();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	CloseGlew();
	return 0;
}
