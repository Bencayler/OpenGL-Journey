// Standard library includes
#include <iostream>
#include <cmath>
#include <vector>

// GLM includes
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Custom shader classes
#include "Texture.h"
#include "Texture.h"

// Custom camera classe(s)
#include "Camera.h"

// Custom buffer classes
#include "EBO.h"
#include "VBO.h"
#include "VAO.h"

#include "Mesh.h"

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
///////////////////////////////////////////////////////////////////////////////
//                  TEXUTRED CUBE VERTICES AND INDICES                       // 
///////////////////////////////////////////////////////////////////////////////
	//                 Cube Coordinates  /                Normals       /               Colors       /        Texture UV   /
	std::vector<Vertex> vertices = {
    // Top face
    Vertex{glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},  // Top-left
	Vertex{glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)}, // Bottom-left
	Vertex{glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)}, // Bottom-right
    Vertex{glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)}, // Top-right

    // Left face
    Vertex{glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // Top-left
    Vertex{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)}, // Bottom-left
    Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)}, // Bottom-right
    Vertex{glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)}, // Top-right

    // Right face
    Vertex{glm::vec3(1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)}, // Top-left
    Vertex{glm::vec3(1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)}, // Bottom-left
    Vertex{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // Bottom-right
    Vertex{glm::vec3(1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)}, // Top-right

    // Front face
    Vertex{glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)}, // Top-left
    Vertex{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // Bottom-left
    Vertex{glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)}, // Top-Right
    Vertex{glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)}, // Bottom-right

    // Back face
    Vertex{glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)}, // Top-left
    Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)}, // Bottom-left
    Vertex{glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // Bottom-right
    Vertex{glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)}, // Top-right

    // Bottom face
    Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // Top-left
    Vertex{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)}, // Bottom-left
    Vertex{glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)}, // Bottom-right
    Vertex{glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)}  // Top-right
};

	std::vector<GLuint> indices = {
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

///////////////////////////////////////////////////////////////////////////////
//                    LIGHT CUBE VERTICES AND INDICES                        // 
///////////////////////////////////////////////////////////////////////////////
	std::vector<Vertex> lightVertices = {
	// X,      Y,      Z
    Vertex{glm::vec3(-1.0f,   1.0f,  -1.0f)},
    Vertex{glm::vec3(-1.0f,   1.0f,   1.0f)},
    Vertex{glm::vec3(1.0f,   1.0f,   1.0f)},
    Vertex{glm::vec3(1.0f,   1.0f,  -1.0f)},
    Vertex{glm::vec3(-1.0f,  -1.0f,  -1.0f)},
    Vertex{glm::vec3(-1.0f,  -1.0f,   1.0f)},
    Vertex{glm::vec3(1.0f,  -1.0f,   1.0f)},
    Vertex{glm::vec3(1.0f,  -1.0f,  -1.0f)}

	};
	std::cout << "Vertex is " << sizeof(Vertex) << " bytes\n";
	std::vector<GLuint> lightIndices = {
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
	// glEnable(GL_CULL_FACE);  // Enable face culling
	glFrontFace(GL_CCW);     // Set front face to counter-clockwise
	// glCullFace(GL_BACK);     // Cull back faces
	

	Shader shader("default.vert", "default.frag");
	Shader lightingShader("light.vert", "light.frag");



	std::vector <std::shared_ptr<Texture>> textures;
	textures.push_back(std::make_shared<Texture>("wood_floor.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE));
	textures.push_back(std::make_shared<Texture>("wood_floor_specular.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE));
	std::vector <std::shared_ptr<Texture>> emptyTextures;
	Mesh cube(vertices, indices, textures);
	Mesh light(lightVertices, lightIndices, emptyTextures);

	glm::vec4 lightColor    = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPosition = glm::vec3(0.0f, 3.0f, 1.0f);
	glm::mat4 lightModel    = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPosition);
	lightModel = glm::scale(lightModel, glm::vec3(0.2f));

	glm::vec3 cubePosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 cubeModel = glm::mat4(1.0f);

	// Now we need to connect our matrices to the lighting shader program
	lightingShader.Activate();
	glUniform4f(glGetUniformLocation(lightingShader.getProgramID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniformMatrix4fv(glGetUniformLocation(lightingShader.getProgramID(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(lightModel));

	
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(cubeModel));
	glUniform4f(glGetUniformLocation(shader.getProgramID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shader.getProgramID(), "lightPos"), lightPosition.x, lightPosition.y, lightPosition.z); 


	// Create the camera object
	Camera Camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 8.0f));

	// Main rendering loop
	while (!glfwWindowShouldClose(window)) {
		// Set the background color
		glClearColor(0.00f, 0.13f, 0.17f, 1.0f);
		// Clear the color and depth buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		
		// Update camera
		Camera.Inputs(window);
		Camera.updateMatrix(45.0f, 0.1f, 100.0f);

		cube.Draw(shader, Camera);
		light.Draw(lightingShader, Camera);
		
		Camera.Matrix(shader, "camMatrix");

		// Swap buffer and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	// Delete our shader program
	shader.Delete();
	lightingShader.Delete();

	// Destroy the window
	glfwDestroyWindow(window);

	// Terminate GLFW
	glfwTerminate();

	// Exit the program
	return 0;
}