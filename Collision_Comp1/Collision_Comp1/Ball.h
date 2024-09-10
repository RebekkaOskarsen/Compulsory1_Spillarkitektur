#ifndef BALL_H
#define BALL_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h> 

class Ball
{
	public:
		Ball();

		void DrawBall();

	private:
		GLuint VAO, VBO, EBO;
};


#endif // !BALL_H


