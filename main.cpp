#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
//mah prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, bool *wfm);
//vertex shader for now...
const char* vertexShaderSource = 
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";
//Fragment shader
const char* fragmentShaderSource = 
	"#version 330\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
	"}\0";
const char* fragmentShaderSource2 =
"#version 330\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";
const char* fragmentShaderSource3 =
"#version 330\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
"}\0";
int main() {

	unsigned int indices[] = {
		0,1,2, //first triangle
	};
	
	//initialize glfw to 3.3 and use opengl core profile
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //sets version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //uses core profile


	//create window
	GLFWwindow* window = glfwCreateWindow(800,600, "Triforce!",NULL,NULL);
	if (window == NULL) { //if window fails to create, display message and exit with error
		std::cout << "failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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
	//fragment shaders
	unsigned int fragmentShader[3];
	fragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
	fragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER);
	fragmentShader[2] = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader[0], 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader[0]);
	glShaderSource(fragmentShader[1], 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader[1]);
	glShaderSource(fragmentShader[2], 1, &fragmentShaderSource3, NULL);
	glCompileShader(fragmentShader[2]);
	//shader programs
	unsigned int shaderProgram[3];
	shaderProgram[0] = glCreateProgram();
	shaderProgram[1] = glCreateProgram();
	shaderProgram[2] = glCreateProgram();
	glAttachShader(shaderProgram[0], vertexShader);
	glAttachShader(shaderProgram[0], fragmentShader[0]);
	glLinkProgram(shaderProgram[0]);
	glAttachShader(shaderProgram[1], vertexShader);
	glAttachShader(shaderProgram[1], fragmentShader[1]);
	glLinkProgram(shaderProgram[1]);
	glAttachShader(shaderProgram[2], vertexShader);
	glAttachShader(shaderProgram[2], fragmentShader[2]);
	glLinkProgram(shaderProgram[2]);
	//check if linking failed
	glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram[0], 512, NULL, infoLog);
	}
	
	//set up vertex data (and Buffer(s)) and configure vertex atributes
	//define triangles
	float firstTriangle[] = {
		0.0f,1.0f,0.0f,
		0.5f,0.0f,0.0f,
		-0.5f,0.0f,0.0f
	};
	float secondTriangle[] = {
		0.5f,0.0f,0.0f,
		0.0f,-1.0f,0.f,
		1.0f,-1.0f,0.0f
	};
	float thirdTriangle[] = {
		-0.5f,0.0f,0.0f,
		-1.0f,-1.0f,0.0f,
		0.0f,-1.0f,0.0f
	};
	
	//create VBOs and VAOs
	unsigned int VBOs[3], VAOs[3];
	glGenVertexArrays(3, VAOs);
	glGenBuffers(3, VBOs);
	//first triangle
	//---------------------------------
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//second triangle
	//---------------------------------
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER,9*sizeof(float), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//third triangle
	//---------------------------------
	glBindVertexArray(VAOs[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), thirdTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//viewport
	glViewport(0, 0, 800, 600);
	bool wireframeMode = 0;
	//render loop
	while (!glfwWindowShouldClose(window)) { //checks if window has been closed
		//input
		processInput(window, &wireframeMode);
		//rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		if (wireframeMode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		//glDrawArrays(GL_TRIANGLES, 0, 9);
		glUseProgram(shaderProgram[0]);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES,0,3);
		
		glUseProgram(shaderProgram[1]);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glUseProgram(shaderProgram[2]);
		glBindVertexArray(VAOs[2]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//check and call events and swap the buffers
		glfwSwapBuffers(window);// swaps the color buffer with the screen buffer
		glfwPollEvents(); //checks events like keyboard entries and such
	}
	
	//delete all GLFW resources
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader[0]);
	glDeleteShader(fragmentShader[1]);
	glDeleteShader(fragmentShader[2]);
	glfwTerminate();
	return 0;
}


//checks keyboard; closes window if escape is pressed
void processInput(GLFWwindow* window, bool *wfm) { 
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		*wfm = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		*wfm = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
//resizes viewport when window is resized.
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}