#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ostream>


GLFWwindow* CreateGlewWindow(int width, int hight, std::string &title, GLFWframebuffersizefun framebuffer_size_callback);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void InitGlew();
void CloseGlew();
bool LoadGlad();

