#include <iostream>
#include <cmath>
#include "shaderClass.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;

		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, 800, 800);


	// Define our triangle vertices
	float vertices[] = {
		// Lower Left : 0
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		// Lower Middle : 1
		0, -0.5f * float(sqrt(3)) / 3, 0.0f,
		// Lower Right : 2
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		// Middle Left : 3
		-0.25f, 0.0f * float(sqrt(3)) / 3, 0.0f,
		// Middle Right : 4 
		0.25f, 0.0f * float(sqrt(3)) / 3, 0.0f,
		// Middle Top : 5
		0.0f, 0.5f * float(sqrt(3)) / 3, 0.0f
	};

	int indices[] = {
		0, 1, 3,
		2, 1, 4,
		3, 4, 5

	};


	// 2. Create the vertex array object and vertex buffer object
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VAO
	glBindVertexArray(VAO);

	//  Bind BVO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Shader shader("default.vert", "default.frag");

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.00f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/*glUseProgram(shaderProgram);*/
		shader.Activate();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

	}

	// Clean up
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	shader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}