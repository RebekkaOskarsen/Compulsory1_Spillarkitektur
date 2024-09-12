#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "Camera.h"
#include "Box.h"
#include "Ball.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int SCR_WIDTH, int SCR_HEIGHT); 
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window); 

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

Camera camera(glm::vec3(0.0f, 2.0f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


int main()
{
	glfwInit(); //Initialize GLFW

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Oblig 1", NULL, NULL);
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

	Box Box1;

	//Balls
	Ball ball1(0.3f, 36, 18, glm::vec3(0.8f, 0.0f, 0.0f)); // Dark Red ball
	Ball ball2(0.3f, 36, 18, glm::vec3(0.0f, 0.7f, 0.0f)); // Dark Green ball
	Ball ball3(0.3f, 36, 18, glm::vec3(0.0f, 0.0f, 0.7f)); // Dark Blue ball
	Ball ball4(0.3f, 36, 18, glm::vec3(0.7f, 0.0f, 1.0f)); // Purple ball
	Ball ball5(0.3f, 36, 18, glm::vec3(1.0f, 1.0f, 0.0f)); // Yellow ball
	Ball ball6(0.3f, 36, 18, glm::vec3(1.0f, 0.5f, 0.0f)); // Orange ball
	Ball ball7(0.3f, 36, 18, glm::vec3(0.0f, 0.0f, 0.0f)); // Black ball
	Ball ball8(0.3f, 36, 18, glm::vec3(1.0f, 0.7f, 1.0f)); // Pink ball
	Ball ball9(0.3f, 36, 18, glm::vec3(0.0f, 0.7f, 1.0f)); // Light Blue ball
	Ball ball10(0.3f, 36, 18, glm::vec3(1.6f, 0.4f, 0.4f)); // Peach ball
	Ball ball11(0.3f, 36, 18, glm::vec3(0.7f, 0.7f, 0.8f)); // Grey ball
	Ball ball12(0.3f, 36, 18, glm::vec3(0.6f, 0.3f, 0.0f)); // Brown ball


	glEnable(GL_DEPTH_TEST);
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window)) // Check if the window should close
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);


		//Render
		glClearColor(0.6f, 0.0f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f); // perspective projection matrix
		shaderProgram.setMat4("projection", projection); // pass the projection matrix to the shader

		glm::mat4 view = camera.GetViewMatrix();
		shaderProgram.setMat4("view", view); // pass the view matrix to the shader

		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		shaderProgram.setMat4("model", model);

		
		// Draw box
		Box1.DrawBox();


		// Draw balls
		model = glm::mat4(1.0f); // Reset model matrix to identity
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, 1.0f)); // 1 row-middle
		shaderProgram.setMat4("model", model);
		ball1.DrawBall(shaderProgram);

		model = glm::mat4(1.0f); // Reset model matrix to identity
		model = glm::translate(model, glm::vec3(1.5f, 0.5f, 1.0f)); // 1 row-right
		shaderProgram.setMat4("model", model);
		ball2.DrawBall(shaderProgram);

		model = glm::mat4(1.0f); // Reset model matrix to identity
		model = glm::translate(model, glm::vec3(-1.5f, 0.5f, 1.0f)); // 1 row-left
		shaderProgram.setMat4("model", model);
		ball3.DrawBall(shaderProgram);

		model = glm::mat4(1.0f); // Reset model matrix to identity
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 1.0f)); // 2 row-middle
		shaderProgram.setMat4("model", model);
		ball4.DrawBall(shaderProgram);

		model = glm::mat4(1.0f); // Reset model matrix to identity
		model = glm::translate(model, glm::vec3(1.5f, 1.5f, 1.0f)); // 2 row-right
		shaderProgram.setMat4("model", model);
		ball5.DrawBall(shaderProgram);

		model = glm::mat4(1.0f); // Reset model matrix to identity
		model = glm::translate(model, glm::vec3(-1.5f, 1.5f, 1.0f)); // 2 row-left
		shaderProgram.setMat4("model", model);
		ball6.DrawBall(shaderProgram);

		model = glm::mat4(1.0f); // Reset model matrix to identity
		model = glm::translate(model, glm::vec3(0.0f, 2.5f, 1.0f)); // 3 row-middle
		shaderProgram.setMat4("model", model);
		ball7.DrawBall(shaderProgram);

		model = glm::mat4(1.0f); // Reset model matrix to identity
		model = glm::translate(model, glm::vec3(1.5f, 2.5f, 1.0f)); // 3 row-right
		shaderProgram.setMat4("model", model);
		ball8.DrawBall(shaderProgram);

		model = glm::mat4(1.0f); // Reset model matrix to identity
		model = glm::translate(model, glm::vec3(-1.5f, 2.5f, 1.0f)); // 3 row-left
		shaderProgram.setMat4("model", model);
		ball9.DrawBall(shaderProgram);

		model = glm::mat4(1.0f); // Reset model matrix to identity
		model = glm::translate(model, glm::vec3(0.0f, 3.5f, 1.0f)); // 4 row-middle
		shaderProgram.setMat4("model", model);
		ball10.DrawBall(shaderProgram);

		model = glm::mat4(1.0f); // Reset model matrix to identity
		model = glm::translate(model, glm::vec3(1.5f, 3.5f, 1.0f)); // 4 row-right
		shaderProgram.setMat4("model", model);
		ball11.DrawBall(shaderProgram);

		model = glm::mat4(1.0f); // Reset model matrix to identity
		model = glm::translate(model, glm::vec3(-1.5f, 3.5f, 1.0f)); // 4 row-left
		shaderProgram.setMat4("model", model);
		ball12.DrawBall(shaderProgram);
		//End ball rendering

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