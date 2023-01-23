#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
//mah prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
int main() {
	//vertex shader for now...
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	//define triangles
	float triforce[] = {
		0.5f,0.5f,0.0f,
		0.0f,-0.5f,0.f,
		0.5f,-0.5f,0.0f,

		0.0f,1.0f,0.0f,
		0.5f,0.5f,0.f,
		-0.5f,0.5f,0.0f,

		-0.5f,0.5f,0.0f,
		0.0f,-0.5f,0.f,
		-0.5f,-0.5f,0.0f
	};
	
	//initialize glfw to 3.3 and use opengl core profile
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //sets version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //uses core profile


	//create window
	GLFWwindow* window = glfwCreateWindow(800,600, "GET JIGGY WITH IT!",NULL,NULL);
	if (window == NULL) { //if window fails to create, display message and exit with error
		std::cout << "failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "failed to initialize Glad" << std::endl;
		return -1;
	}
	//compile shaders
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//fragment shader
	
	//do the vbo stuff
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triforce),triforce, GL_STATIC_DRAW);
	
	//viewport
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//render loop
	while (!glfwWindowShouldClose(window)) { //checks if window has been closed
		//input
		processInput(window);
		//rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//check and call events and swap the buffers
		glfwSwapBuffers(window);// swaps the color buffer with the screen buffer
		glfwPollEvents(); //checks events like keyboard entries and such
	}
	
	//delete all GLFW resources
	glfwTerminate();
	return 0;
}


//checks keyboard; closes window if escape is pressed
void processInput(GLFWwindow* window) { 
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
//resizes viewport when window is resized.
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}