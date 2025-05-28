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

	// Import texture
	int widthImg, heightImg, nrChannelsImg;
	unsigned char *imageData = stbi_load("C:\\Users\\THEJANKMACHINE\\Documents\\VSCode\\OpenGL_Journals_Test\\05-3DCubeTextured\\shaders\\assets\\wood_floor.png", &widthImg, &heightImg, &nrChannelsImg, 0);
	// unsigned char *imageData = stbi_load("wood_flooring.png", &widthImg, &heightImg, &nrChannelsImg, 0);

	// Check if the image was loaded successfully
	if (imageData == nullptr) {
		std::cerr << "Failed to load texture" << std::endl;
	}
	// std::cout << imageData << std::endl;
	// std::cout << "Image loaded with dimensions: " << widthImg << "x" << heightImg << " and channels: " << nrChannelsImg << std::endl;

	// Generate a texture ID, activate a texture unit, and bind the texture
	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0); // Activate texture unit 0
	glBindTexture(GL_TEXTURE_2D, texture); // Bind the texture

	// Set texture wrapping to repeglUniform1i(glGetUniformLocation(shader.getProgramID(), "textureSampler"), 0);at
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); 
	
	// Upload the texture data to the GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	// Generate mipmaps for the texture
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free the image data after uploading to the GPU
	stbi_image_free(imageData);

	// Main rendering loop
	while (!glfwWindowShouldClose(window)) {
		
		// Simple timer to rotate the cube
		double currentTime = glfwGetTime();
		if (currentTime - previousTime >= 1 / 160.0) { // 60 FPS
			rotation    += 0.01f; // Rotate by 0.01 radians
			previousTime = currentTime;
		}


		glClearColor(0.00f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffers
		
		// Activate our shader program
		shader.Activate();

		// Set the texture sampler uniform to use texture unit 0
		glUniform1i(glGetUniformLocation(shader.getProgramID(), "textureSampler"), 0);

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
			1000.0f              // Far visible plane
		);

	
		
		// Get the uniform locations for our matrices
		GLuint modelLocation = glGetUniformLocation(shader.getProgramID(), "mModel");
		GLuint viewLocation  = glGetUniformLocation(shader.getProgramID(), "mView");
		GLuint projLocation  = glGetUniformLocation(shader.getProgramID(), "mProjection");

		glUniform1i(glGetUniformLocation(shader.getProgramID(), "textureSampler"), 0);

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

	// Delete the texture
	glDeleteTextures(1, &texture);

	// Delete our shader program
	shader.Delete();

	// Destroy the window
	glfwDestroyWindow(window);

	// Terminate GLFW
	glfwTerminate();
	return 0;
}