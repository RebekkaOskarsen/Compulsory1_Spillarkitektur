#ifndef BALL_H
#define BALL_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h> 

#include "shaderClass.h"

class Ball
{
	public:
		Ball(float radius, int sectorCount, int stackCount, glm::vec3 color);

		void DrawBall(Shader &shader);
		~Ball();

	private:
		void generateBall();

		float radius;
		int sectorCount;
		int stackCount;
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		glm::vec3 color;

		unsigned int VAO, VBO, EBO;
};


#endif // !BALL_H


