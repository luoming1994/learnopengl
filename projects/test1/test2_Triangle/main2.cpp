#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../learnopengl/Utils.h"
#include "../learnopengl/MeshFile.h"
typedef unsigned int ShaderType;

void MainLoop(GLFWwindow *window, GLuint shader, GLuint VAO);
GLuint CompileShader(const char* str_code, ShaderType	shader_type);
GLuint LinkShader(GLuint *shaders, int len, bool del_shader = true);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
std::string TITLE = "OpenGL";

const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";


int main()
{
	InitGlew();

	GLFWwindow* window = CreateGlewWindow(SCR_WIDTH, SCR_HEIGHT, TITLE, framebuffer_size_callback);
	if (window == NULL)	return -1;
	if (!LoadGlad())	return -1;

	GLuint vertexShader = CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
	GLuint fragmentShader = CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
	GLuint shaders[2] = { vertexShader ,fragmentShader };
	GLuint shaderProgram = LinkShader(shaders, 2);

	//	设置定点数据 顶点缓存 定点属性
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	//	定点索引 从零开始
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	//	顶点数组对象(Vertex Array Object, VAO) 任何顶点属性调用 在个VAO
	//	顶点缓冲对象(Vertex Buffer Objects, VBO)，显存中
	//	索引缓冲对象(Element Buffer Object，EBO)(Index Buffer Object，IBO) 
	//	If you're on OpenGL-4 core, you need to create a VAO first, otherwise nothing will draw。
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	//GLuint VAO, VBO, EBO;
	////	创建VAO
	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);
	////	创建VBO
	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	////	创建EBO
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	////	设置顶点属性
	////	通过glBindAttribLocation设置顶点属性指针
	////	vt指绑定到的顶点着色器的input，
	////	vs指该vbo中顶点的成分数，比如法线为3个float，uv为2个float
	//GLuint vt = 0;
	//GLuint vs = 3;
	////glBindVertexArray(VAO);
	////glBindBuffer(GL_ARRAY_BUFFER, VBO);
	////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glEnableVertexAttribArray(vt);
	//glVertexAttribPointer(vt, vs, GL_FLOAT, GL_FALSE, vs * sizeof(float), (void*)0);
	
	Mesh mesh(vertices, sizeof(vertices) / sizeof(*vertices), indices, sizeof(indices) / sizeof(*indices));
	GLint locations[1] = { 3 };
	mesh.SetVerticesAttribute(locations, 1);
	
	//	清除绑定
	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//	不要在AVO激活状态解除对应EBO的绑定
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// 线框模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw our first triangle
		glUseProgram(shaderProgram);
		//glBindVertexArray(VAO); // 只有一个VAO，可以不需要每次都设置
		////glDrawArrays(GL_TRIANGLES, 0, 6);			//	VBO
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	//	使用EBO
		//// glBindVertexArray(0); // no need to unbind it every time 
		mesh.UseMesh();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// 可选 清除顶点资源
	/*glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);*/

	CloseGlew();
	return 0;
}





//	输出Shader错误信息
void PrintShaderFailInfo(GLuint shader, GLenum pname,const char *ext_str)
{
	GLint success;
	switch (pname)
	{
	case GL_COMPILE_STATUS:
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		break;
	case GL_LINK_STATUS:
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
	default:
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		break;
	}
	char infoLog[512];
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << ext_str <<"\n" << infoLog << std::endl;
	}
}

//	编译Shader
GLuint CompileShader(const char* str_code, ShaderType	shader_type)
{
	GLuint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &str_code, NULL);
	glCompileShader(shader);

	PrintShaderFailInfo(shader, GL_COMPILE_STATUS, "ERROR::SHADER::COMPILATION_FAILED");
	return shader;
}

//	链接Shader
GLuint LinkShader(GLuint *shaders, int len, bool del_shader)
{
	// link shaders
	GLuint shaderProgram = glCreateProgram();
	for (int i = 0; i < len; i++)
		glAttachShader(shaderProgram, shaders[i]);
	glLinkProgram(shaderProgram);
	PrintShaderFailInfo(shaderProgram, GL_LINK_STATUS, "ERROR::SHADER::LINK_FAILED");
	if (del_shader)
		for (int i = 0; i < len; i++)
			glDeleteShader(shaders[i]);
	return shaderProgram;
}

//	渲染循环
void MainLoop(GLFWwindow *window ,GLuint shader, GLuint VAO)
{
	// render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw our first triangle
		glUseProgram(shader);
		glBindVertexArray(VAO); // 只有一个VAO，可以不需要每次都设置
		//glDrawArrays(GL_TRIANGLES, 0, 6);			//	VBO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	//	使用EBO
		// glBindVertexArray(0); // no need to unbind it every time 

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

