#include <iostream>
#include <cmath>

// Shader class
#include "shaderClass.h"

// Custom buffer classes
#include "EBO.h"
#include "VBO.h"
#include "VAO.h"

// Include GLAD and GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>


int main() {
	// Define our triangle vertices
	GLfloat vertices[] = {
	// X,      Y,                         Z      R,    G,    B	
     -0.5f, -0.5f * float(sqrt(3)) / 2,  0.0f,  1.0f, 0.0f, 0.0f, // Bottom-left (Red)
      0.0f, -0.5f * float(sqrt(3)) / 2,  0.0f,  1.0f, 1.0f, 0.0f, // Bottom-middle (Yellow)
      0.5f, -0.5f * float(sqrt(3)) / 2,  0.0f,  0.0f, 1.0f, 0.0f, // Bottom-right (Green)
    -0.25f,  0.0f,                       0.0f,  0.5f, 0.0f, 0.5f, // Middle-left (violet)
     0.25f,  0.0f,                       0.0f,  0.0f, 1.0f, 1.0f, // Middle-right (Cyan)
      0.0f,  0.5f * float(sqrt(3)) / 2,  0.0f,  0.0f, 0.0f, 1.0f  // Top (Blue)
	};


		
	// Define our triangle indices 
	// See the diagram below for the indices and what corresponding vertices they refer to.
	/*  
	    5
	   / \
	  3 - 4
	 / \ / \
	0 - 1 - 2 
	*/
	GLuint indices[] = {
		0, 1, 3, // Bottom left triangle
		3, 4, 1, // Middle triangle
		1, 2, 4, // Bottom right triangle
		3, 4, 5  // Top triangle

	};

	// Initialize GLFW
	glfwInit();

	// Tell GLFW to use OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW to use the core CORE profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFW window
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
	// Error handling for window creation
	if (window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD to configure OpenGL
	gladLoadGL();

	// Set our viewport X / y and width / height
	glViewport(0, 0, 800, 800);

	// Create and compile our shaders
	Shader shader("default.vert", "default.frag");

	// Create VAO, VBO, and EBO objects
	VAO vao;
	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));

	// Bind the VAO, VBO, and EBO objects to buffers
	vao.Bind();
	vbo.Bind();	
	ebo.Bind();
	
	// Link VBO to VAO
	vao.LinkVBO(vbo, 0, 3, 6 * sizeof(GLfloat), 0);               // Position attribute
	vao.LinkVBO(vbo, 1, 3, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat)); // Color attribute

	
	// Unbind VAO, VBO, and EBO
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.00f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/*glUseProgram(shaderProgram);*/
		shader.Activate();
		glBindVertexArray(vao.vaoID);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

	}

	// Delete our objects
	vao.Delete();
	vbo.Delete();
	ebo.Delete();

	// Delete our shader program
	shader.Delete();

	// Destroy the window
	glfwDestroyWindow(window);

	// Terminate GLFW
	glfwTerminate();
	return 0;
}