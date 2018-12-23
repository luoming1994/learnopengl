#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../learnopengl/Utils.h"
#include <iostream>


void MainLoop(GLFWwindow* window);
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

	MainLoop(window);
	CloseGlew();
	return 0;
}




void MainLoop(GLFWwindow* window)
{
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}


