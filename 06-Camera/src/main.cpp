// Standard library includes
#include <iostream>
#include <cmath>

// GLM includes
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Custom shader classes
#include "shaderClass.h"
#include "textureClass.h"

// Custom camera classe(s)
#include "Camera.h"

// Custom buffer classes
#include "EBO.h"
#include "VBO.h"
#include "VAO.h"

// Include GLAD and GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// THE ONE AND ONLY PREPROCESSOR MACRO TO INCLUDE THE STB IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

// Constants for the height and width of the scene
const unsigned int HEIGHT = 800;
const unsigned int WIDTH  = 800;

int main() {
	// Define our triangle vertices
	GLfloat vertices[] = {

	/*
	Like we see below with the indices, the vetices don't get more complicated
	in the sense of dimension, but the nature of texture mapping makes
	this considerably more difficuly. Essentially every face is unique
	and not ACTUALLY connected, but the coordinates match and they will 
	all rotate together. All this is to say, the number of vertices goes
	up considerably. We have 3 * 4 * 6 = 72 vertices now, just because 
	every face has to have a unique coordinate and we can no longer share
	and connect them via the indices. The U, V are normalized coordinates
	to stretch the texture over the face. This too needs to match its 
	corresponding vertex or the whole texture will be smeared and warped
	at best. This adds considerable complexity, not in terms of execution
	but in terms of debugging. The values must be perfect, and finding the 
	imperfect value took 2 hours. 
	(0, 1) ------- (1, 1)
	|				 |
	|				 |
	|				 |
	| 				 |
	(0, 0) ------- (1, 0)
	*/

	// X,     Y,      Z       U,    V
    // Top face
    -1.0f,  1.0f, -1.0f,  0.0f, 0.0f, // Top-left
    -1.0f,  1.0f,  1.0f,  0.0f, 1.0f, // Bottom-left
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f, // Bottom-right
     1.0f,  1.0f, -1.0f,  1.0f, 0.0f, // Top-right

    // Left face
    -1.0f,  1.0f,  1.0f,  0.0f, 0.0f, // Top-left
    -1.0f, -1.0f,  1.0f,  0.0f, 1.0f, // Bottom-left
    -1.0f, -1.0f, -1.0f,  1.0f, 1.0f, // Bottom-right
    -1.0f,  1.0f, -1.0f,  1.0f, 0.0f, // Top-right

    // Right face
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f, // Top-left
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f, // Bottom-left
     1.0f, -1.0f, -1.0f,  0.0f, 0.0f, // Bottom-right
     1.0f,  1.0f, -1.0f,  0.0f, 1.0f, // Top-right

    // Front face
    -1.0f,  1.0f,  1.0f,  0.0f, 1.0f, // Top-left
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, // Bottom-left
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f, // Bottom-right
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f, // Top-right

    // Back face
    -1.0f,  1.0f, -1.0f,  1.0f, 1.0f, // Top-left
    -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, // Bottom-left
     1.0f, -1.0f, -1.0f,  0.0f, 0.0f, // Bottom-right
     1.0f,  1.0f, -1.0f,  0.0f, 1.0f, // Top-right

    // Bottom face
    -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, // Top-left
    -1.0f, -1.0f,  1.0f,  0.0f, 1.0f, // Bottom-left
     1.0f, -1.0f,  1.0f,  1.0f, 1.0f, // Bottom-right
     1.0f, -1.0f, -1.0f,  1.0f, 0.0f  // Top-right
};


		
	/*	
	Define our square indices:

	This is a bit outdated for the texture program just because we deal with
	indices differently. We can no longer share incides like we can with the
	rainbow cube. Because we are placing a texture onto the local coordinates
 	of the cube face, the indices need to be unique. In the number of indices
	nothing changes. We still need to tell the GPU how to connect the inidces,
	but inpractice it is much more difficult because the unique values has 
	increased. We need 24 values (4 for each side) as opposed to the 6 
	(one for each point that could be shared) we werere able to share for 
	all 36 indices before.
	
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
    0, 1, 2, 
	0, 2, 3,
    
	// Left face
    4, 5, 6,
	4, 6, 7,
    
	// Right face
    8, 9, 10,
	8, 10, 11,
    
	// Front face
    12, 13, 14, 
	12, 14, 15,
    
	// Back face
    16, 17, 18,
	16, 18, 19,
    
	// Bottom face
    20, 21, 22, 
	20, 22, 23
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
	// glEnable(GL_CULL_FACE);  // Enable face culling
	glFrontFace(GL_CCW);     // Set front face to counter-clockwise
	// glCullFace(GL_BACK);     // Cull back faces

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
	vao.LinkAttrib(vbo, 0, 3, 5 * sizeof(GLfloat), 0);                   // Position attribute
	vao.LinkAttrib(vbo, 1, 2, 5 * sizeof(GLfloat), 3 * sizeof(GLfloat)); // Texture attribute
	
	// Unbind VAO, VBO, and EBO
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	// Initialize a timer for rotation
	GLfloat rotation      = 0.0f;
	GLdouble previousTime = glfwGetTime();

	// Create a texture object
	textureClass texture(
		"wood_floor.png",
		GL_TEXTURE_2D, 
		GL_TEXTURE0,
		GL_RGBA,
		GL_UNSIGNED_BYTE
	);

	// Attach the uniform shader variable to the shader program and the texture
	// unit
	texture.textureUnit(shader, "textureSampler", 0);

	// Create the camera object
	Camera Camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 8.0f));


	// Main rendering loop
	while (!glfwWindowShouldClose(window)) {
		
		// Simple timer to rotate the cube
		double currentTime = glfwGetTime();
		if (currentTime - previousTime >= 1 / 160.0) { // 60 FPS
			rotation    += 0.01f; // Rotate by 0.01 radians
			previousTime = currentTime;
		}

		// Add rotation for the sake of exercise
		// I'll revert this later, but it is neat to work with the shader 
		// and get the locations and pass it back to the vertex shader. 
		// This is the kind of exercise I should do more often.
		glm::mat4 model = glm::rotate(glm::mat4(1.0f),
						  rotation,
						  glm::vec3(0.5f, 1.0f, 0.25f)

	);

		// Get the mModel location
		GLuint modelLocation = glGetUniformLocation(shader.getProgramID(), "mModel");
		// Pass that location back to the vertex shader
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		// Set the background color
		glClearColor(0.00f, 0.13f, 0.17f, 1.0f);
		// Clear the color and depth buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		
		// Activate our shader program
		shader.Activate();

		// Bind the texture
		texture.Bind();

		// Set the texture sampler uniform to use texture unit 0
		glUniform1i(glGetUniformLocation(shader.getProgramID(), "textureSampler"), 0);

		Camera.Matrix(45.0f, 0.0f, 100.0, shader, "camMatrix");
		Camera.Inputs(window);

		// Get the uniform location for the texture in fragment shader
		glUniform1i(glGetUniformLocation(shader.getProgramID(), "textureSampler"), 0);


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

	// Delete the texture
	//glDeleteTextures(1, &texture);
	texture.Delete();

	// Delete our shader program
	shader.Delete();

	// Destroy the window
	glfwDestroyWindow(window);

	// Terminate GLFW
	glfwTerminate();

	// Exit the program
	return 0;
}