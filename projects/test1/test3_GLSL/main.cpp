#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../learnopengl/Utils.h"
#include "../learnopengl/MeshFile.h"
#include "ShaderFile.h"

#include <iostream>


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

	// build and compile our shader program
	// Shader ourShader("shader.vs", "shader.fs");
	Shader ourShader("shader.vs", "shader_uniform.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(*vertices));
	GLint location[2] = { 3,3 };
	mesh.SetVerticesAttribute(location, 2);
	//unsigned int VBO, VAO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glBindVertexArray(VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//// position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	// glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		
		// render the triangle
		ourShader.UseShader();
		ourShader.Set4Float("ourColor", 0.0f, greenValue, 0.0f, 1.0f);
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		mesh.UseMesh();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);

	
	CloseGlew();
	return 0;
}

