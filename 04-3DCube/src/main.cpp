#include <iostream>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shader class
#include "shaderClass.h"

// Custom buffer classes
#include "EBO.h"
#include "VBO.h"
#include "VAO.h"

// Include GLAD and GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const unsigned int HEIGHT = 800;
const unsigned int WIDTH  = 800;



int main() {
	// Define our triangle vertices
	GLfloat vertices[] = {
	// X,      Y,      Z        R,   G,    B	
    -1.0f,   1.0f,  -1.0f,    1.0f, 0.0f, 0.0f,  // Vertex 0: (Red)
    -1.0f,   1.0f,   1.0f,    1.0f, 1.0f, 0.0f,  // Vertex 1: (Yellow)
     1.0f,   1.0f,   1.0f,    0.0f, 1.0f, 0.0f,  // Vertex 2: (Green)
     1.0f,   1.0f,  -1.0f,    1.0f, 0.0f, 1.0f,  // Vertex 3: (Magenta)
    -1.0f,  -1.0f,  -1.0f,    0.0f, 0.0f, 1.0f,  // Vertex 4: (Blue)
    -1.0f,  -1.0f,   1.0f,    0.0f, 1.0f, 1.0f,  // Vertex 5: (Cyan)
     1.0f,  -1.0f,   1.0f,    1.0f, 1.0f, 1.0f,  // Vertex 6: (White)
     1.0f,  -1.0f,  -1.0f,    1.0f, 0.0f, 0.5f   // Vertex 7: (Pink)
};


		
	// Define our square indices 
	// For the sake of an example. We will create a square with 6 vertices and 12 indices
	// But it helps to visualize the square as a triangle mesh.
	/*  
     3 ______ 2	
	 /     /|
	/     / |
  	0 -- 1__|
  5	| \  |  / 7
	|  \ | /
	4 -- 6
	*/
	GLuint indices[] = {
		// Top face
		0, 1, 2, // Triangle 1
		0, 2, 3, // Triangle 2

		// Bottom face
		4, 6, 5, // Triangle 1
		4, 7, 6, // Triangle 2
	
		// Left face
		0, 5, 1, // Triangle 1
		0, 4, 5, // Triangle 2
		
		// Right face
		3, 2, 6, // Triangle 1
		3, 6, 7, // Triangle 2

		// Front face
		1, 5, 6,  // Triangle 1
		1, 6, 2,  // Triangle 2
		
		// Back face
		0, 3, 7, // Triangle 1
		0, 7, 4  // Triangle 2
	};

	// Initialize GLFW
	if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
}

	// Tell GLFW to use OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW to use the core CORE profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFW window
	GLFWwindow* window = glfwCreateWindow(1000, 1000, "OpenGL", NULL, NULL);
	// Error handling for window creation
	if (window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	
	// Load GLAD to configure OpenGL
	if(!gladLoadGL()) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Set our viewport X / y and width / height
	glViewport(0, 0, WIDTH, HEIGHT);


	// Enable GL features we need for 3D rendering
	glEnable(GL_DEPTH_TEST); // Enable depth testing
	glEnable(GL_CULL_FACE);  // Enable face culling
	glFrontFace(GL_CCW);     // Set front face to counter-clockwise
	glCullFace(GL_BACK);     // Cull back faces

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
	vao.LinkAttrib(vbo, 0, 3, 6 * sizeof(GLfloat), 0);               // Position attribute
	vao.LinkAttrib(vbo, 1, 3, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat)); // Color attribute

	
	// Unbind VAO, VBO, and EBO
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	// Initialize a timer for rotation
	GLfloat rotation       = 0.0f;
	GLdouble previousTime = glfwGetTime();


	// Main rendering loop
	while (!glfwWindowShouldClose(window)) {
	
		glClearColor(0.00f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Activate our shader program
		shader.Activate();

		// Simple timer to rotate the cube
		double currentTime = glfwGetTime();
		if (currentTime - previousTime >= 1 / 160.0) { // 60 FPS
			rotation    += 0.01f; // Rotate by 0.01 radians
			previousTime = currentTime;
		}



		// Initialize our mode, view, and projection matrices
		glm::mat4 model      = glm::mat4(1.0f);
		glm::mat4 view       = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);


		model = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.5f, 1.0f, 0.0f)); // Apply rotation

		view = glm::translate(
			view,                        // Apply the back onto the view matrix
			glm::vec3(0.0f, 0.0f, -8.0f) // Move the camera back
		);

		projection = glm::perspective(
			glm::radians(45.0f), // Field of view in degrees
		    static_cast<float>(WIDTH) / static_cast<float>(HEIGHT),     // Aspect ratio (the same as the window size)
			0.1f,                // Near visible plane
			100.0f               // Far visible plane
		);

	
		
		// Get the uniform locations for our matrices
		GLuint modelLocation = glGetUniformLocation(shader.getProgramID(), "mModel");
		GLuint viewLocation  = glGetUniformLocation(shader.getProgramID(), "mView");
		GLuint projLocation  = glGetUniformLocation(shader.getProgramID(), "mProjection");


		// Pass the matrices to our shaders
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));


		// Bind the VAO and draw the cube
		glBindVertexArray(vao.vaoID);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

		// Swap buffer and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();

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