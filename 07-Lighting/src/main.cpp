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
///////////////////////////////////////////////////////////////////////////////
//                  TEXUTRED CUBE VERTICES AND INDICES                       // 
///////////////////////////////////////////////////////////////////////////////
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

	// Cube Coordinates  / TexCoords   /      Normals
    // Top face
    -1.0f,  1.0f, -1.0f,   0.0f, 0.0f,   0.0f, 1.0f, 0.0f,      // Top-left
    -1.0f,  1.0f,  1.0f,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f,     // Bottom-left
     1.0f,  1.0f,  1.0f,   1.0f, 1.0f,   0.0f, 1.0f, 0.0f,      // Bottom-right
     1.0f,  1.0f, -1.0f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,      // Top-right

    // Left face
    -1.0f,  1.0f,  1.0f,   0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,      // Top-left
    -1.0f, -1.0f,  1.0f,   0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,     // Bottom-left
    -1.0f, -1.0f, -1.0f,   1.0f, 1.0f,   -1.0f, 0.0f, 0.0f,     // Bottom-right
    -1.0f,  1.0f, -1.0f,   1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,     // Top-right

    // Right face
     1.0f,  1.0f,  1.0f,   1.0f, 1.0f,    1.0f, 0.0f, 0.0f,     // Top-left
     1.0f, -1.0f,  1.0f,   1.0f, 0.0f,    1.0f, 0.0f, 0.0f,     // Bottom-left
     1.0f, -1.0f, -1.0f,   0.0f, 0.0f,    1.0f, 0.0f, 0.0f,     // Bottom-right
     1.0f,  1.0f, -1.0f,   0.0f, 1.0f,    1.0f, 0.0f, 0.0f,     // Top-right

    // Front face
    -1.0f,  1.0f,  1.0f,   0.0f, 1.0f,    0.0f, 0.0f, 1.0f,     // Top-left
    -1.0f, -1.0f,  1.0f,   0.0f, 0.0f,    0.0f, 0.0f, 1.0f,     // Bottom-left
     1.0f, -1.0f,  1.0f,   1.0f, 0.0f,    0.0f, 0.0f, 1.0f,     // Bottom-right
     1.0f,  1.0f,  1.0f,   1.0f, 1.0f,    0.0f, 0.0f, 1.0f,     // Top-right

    // Back face
    -1.0f,  1.0f, -1.0f,   1.0f, 1.0f,   0.0f, 0.0f, -1.0f,     // Top-left
    -1.0f, -1.0f, -1.0f,   1.0f, 0.0f,   0.0f, 0.0f, -1.0f,     // Bottom-left
     1.0f, -1.0f, -1.0f,   0.0f, 0.0f,   0.0f, 0.0f, -1.0f,     // Bottom-right
     1.0f,  1.0f, -1.0f,   0.0f, 1.0f,   0.0f, 0.0f, -1.0f,     // Top-right

    // Bottom face
    -1.0f, -1.0f, -1.0f,   0.0f, 0.0f,   0.0f, -1.0f, 0.0f,     // Top-left
    -1.0f, -1.0f,  1.0f,   0.0f, 1.0f,   0.0f, -1.0f, 0.0f,     // Bottom-left
     1.0f, -1.0f,  1.0f,   1.0f, 1.0f,   0.0f, -1.0f, 0.0f,     // Bottom-right
     1.0f, -1.0f, -1.0f,   1.0f, 0.0f,   0.0f, -1.0f, 0.0f      // Top-right
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

///////////////////////////////////////////////////////////////////////////////
//                    LIGHT CUBE VERTICES AND INDICES                        // 
///////////////////////////////////////////////////////////////////////////////
// We can just copy these from the interpolated cube and skip the color data
	GLfloat lightVertices[] = {
	// X,      Y,      Z
    -1.0f,   1.0f,  -1.0f,
    -1.0f,   1.0f,   1.0f,
     1.0f,   1.0f,   1.0f,
     1.0f,   1.0f,  -1.0f,
    -1.0f,  -1.0f,  -1.0f,
    -1.0f,  -1.0f,   1.0f,
     1.0f,  -1.0f,   1.0f,
     1.0f,  -1.0f,  -1.0f

	};

	GLuint lightIndices[] = {
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
	
	///////////////////////////////////
	// Textured cube initialization  //
	///////////////////////////////////
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
	vao.LinkAttrib(vbo, 0, 3, 8 * sizeof(GLfloat), 0);                   // Position attribute
	vao.LinkAttrib(vbo, 1, 2, 8 * sizeof(GLfloat), 3 * sizeof(GLfloat)); // Texture attribute
	vao.LinkAttrib(vbo, 2, 3, 8 * sizeof(GLfloat), 5 * sizeof(GLfloat)); // Normal Attributes
	
	// Unbind VAO, VBO, and EBO
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

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

	///////////////////////////////////
	// Lighting cube initialization  //
	///////////////////////////////////
	Shader lightingShader("light.vert", "light.frag");

	VAO lightVao;
	VBO lightVbo(lightVertices, sizeof(lightVertices));
	EBO lightEbo(lightIndices, sizeof(lightIndices));

	lightVao.Bind();
	lightVbo.Bind();
	lightEbo.Bind();

	// Attach the vertices to the VAO 
	lightVao.LinkAttrib(lightVbo, 0, 3, 3 * sizeof(GLfloat), 0);

	// Unbind the VAO, VBO, EBO objects 
	lightVao.Unbind();
	lightVbo.Unbind();
	lightEbo.Unbind();

	glm::vec4 lightColor    = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPosition = glm::vec3(4.0f, 2.0f, 0.0f);
	glm::mat4 lightModel    = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPosition);
	lightModel = glm::scale(lightModel, glm::vec3(0.2f));

	glm::vec3 cubePosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 cubeModel = glm::mat4(1.0f);

	// Now we need to connect our matrices to the lighting shader program
	lightingShader.Activate();
	glUniform4f(
		glGetUniformLocation(lightingShader.getProgramID(), "lightColor"),
		lightColor.x, lightColor.y, lightColor.z, lightColor.w
	);
	glUniformMatrix4fv(glGetUniformLocation(lightingShader.getProgramID(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(lightModel));

	
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(cubeModel));
	glUniform4f(
    	glGetUniformLocation(shader.getProgramID(), "lightColor"),
    	lightColor.x, lightColor.y, lightColor.z, lightColor.w
	);




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

		///////////////////////////////////////////////////
		//        TEXTURED CUBE RENDERING LOOP           //
		///////////////////////////////////////////////////
		shader.Activate();
		texture.Bind();
		Camera.Matrix(shader, "camMatrix");

		// Set light color for textured cube
		glUniform4f(
			glGetUniformLocation(shader.getProgramID(), "lightColor"),
			lightColor.x, lightColor.y, lightColor.z, lightColor.w
		);


		// Pass light position to the textured cube's shader
		glUniform3f(
			glGetUniformLocation(shader.getProgramID(), "lightPos"),
			lightPosition.x, lightPosition.y, lightPosition.z
		);

		// Pass camera position to the textures cube's shader (for specular) 
		glUniform3f (
			glGetUniformLocation(shader.getProgramID(), "camPos"),
			Camera.Position.x, Camera.Position.y, Camera.Position.z
		);


		// Draw textured cube
		vao.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);


		///////////////////////////////////////////////////
		//        LIGHTING CUBE RENDERING LOOP           //
		///////////////////////////////////////////////////
		lightingShader.Activate();
		Camera.Matrix(lightingShader, "camMatrix");

		// Update model matrix uniform
		glUniformMatrix4fv(
			glGetUniformLocation(lightingShader.getProgramID(), "modelMatrix"), 
			1, GL_FALSE, 
			glm::value_ptr(lightModel)
		);

		// Set light color
		glUniform4f(
			glGetUniformLocation(lightingShader.getProgramID(), "lightColor"),
			lightColor.x, lightColor.y, lightColor.z, lightColor.w
		);

		// Bind light VAO and draw
		lightVao.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);


		// glUniformMatrix4fv(glGetUniformLocation(lightingShader.getProgramID(), "modelMatrix"), 
        //            1, GL_FALSE, glm::value_ptr(lightModel));



		// // Set the texture sampler uniform to use texture unit 0
		// glUniform1i(glGetUniformLocation(shader.getProgramID(), "textureSampler"), 0);



		// // Bind the VAO and draw the cube
		// glBindVertexArray(vao.vaoID);
		// glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

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