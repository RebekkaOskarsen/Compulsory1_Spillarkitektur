#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "Camera.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int SCR_WIDTH, int SCR_HEIGHT); 
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window); 

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

GLfloat boxvertices[] =
{
	//position				//Color
	//Bottom wall
	-2.0f, 0.0f, 2.0f,		1.0f, 0.0f, 0.0f,
	 2.0f, 0.0f, 2.0f,		1.0f, 0.0f, 0.0f,
	 2.0f, 0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	-2.0f, 0.0f, 0.0f,		1.0f, 0.0f, 0.0f,

	//Back wall
	-2.0f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	 2.0f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	 2.0f, 3.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-2.0f, 3.0f, 0.0f,		0.0f, 1.0f, 0.0f,

	//Left wall
	-2.0f, 0.0f, 2.0f,		0.0f, 0.0f, 1.0f,
	-2.0f, 0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	-2.0f, 3.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	-2.0f, 3.0f, 2.0f,		0.0f, 0.0f, 1.0f,

	//Right wall
	 2.0f, 0.0f, 2.0f,		0.0f, 0.0f, 1.0f,
	 2.0f, 0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	 2.0f, 3.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	 2.0f, 3.0f, 2.0f,		0.0f, 0.0f, 1.0f,

	 //Top wall
	-2.0f, 3.0f, 2.0f,		1.0f, 0.0f, 1.0f,
	 2.0f, 3.0f, 2.0f,		1.0f, 0.0f, 1.0f,
	 2.0f, 3.0f, 0.0f,		1.0f, 0.0f, 1.0f,
	-2.0f, 3.0f, 0.0f,		1.0f, 0.0f, 1.0f,

};

GLuint boxindices[] =
{
	0, 1, 2,
	0, 2, 3,

	4, 5, 6,
	4, 6, 7,

	8, 9, 10,
	8, 10, 11,

	12, 13, 14,
	12, 14, 15,

	16, 17, 18,
	16, 18, 19
};

int main()
{
	glfwInit(); //Initialize GLFW

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Compulsory 3", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetCursorPosCallback(window, mouse_callback);
	// Camera #9
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // tell GLFW to capture our mouse

	//Initialize GLAD
	gladLoadGL();

	//Set the viewport
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	Shader shaderProgram("default.vert", "default.frag");

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(boxvertices), boxvertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boxindices), boxindices, GL_STATIC_DRAW);

	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	
	while (!glfwWindowShouldClose(window)) // Check if the window should close
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);


		//Render
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f); // perspective projection matrix
		shaderProgram.setMat4("projection", projection); // pass the projection matrix to the shader

		glm::mat4 view = camera.GetViewMatrix();
		shaderProgram.setMat4("view", view); // pass the view matrix to the shader

		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		shaderProgram.setMat4("model", model);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, sizeof(boxindices) / sizeof(int), GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int SCR_WIDTH, int SCR_HEIGHT)
{
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	std::cout << "Window resized with " << SCR_WIDTH << "Height" << SCR_HEIGHT << std::endl;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

	if (firstMouse)
	{
		lastX = static_cast<float>(xpos);   // Update lastX with xpos
		lastY = static_cast<float>(ypos);   // Update lastY with ypos
		firstMouse = false;
	}

	float xoffset = static_cast<float>(xpos) - lastX;
	float yoffset = lastY - static_cast<float>(ypos); // reversed since y-coordinates go from bottom to top

	lastX = static_cast<float>(xpos);
	lastY = static_cast<float>(ypos);

	camera.ProcessMouseMovement(xoffset, yoffset);
}