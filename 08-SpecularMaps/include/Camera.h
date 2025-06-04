#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

// Graphics library imports
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

// Custom class include
#include "shaderClass.h"

class Camera {
    private:
        /*
        Nothing for now
        */

    public:
        glm::vec3 Position; // For the location of the camera
        glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f) ; // For the direction of the camera
        glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
        
        glm::mat4 cameraMatrix = glm::mat4(1.0f);
        
        
        int width;
        int height;

        bool firstClick;

        // Speed of the camera moving through space
        float speed = 0.1f;
        // Speed of camera movement
        float sensitivity = 100.0f;

        // Constructor declaration
        Camera(int width, int height, glm::vec3 position);
        
        void updateMatrix(float FOVdeg, float nearPlane, float farPlane);

        // Matrix function to send the matrices to the shader - basically a wrapper around our various 
        // Camera based matrices in the main function
        void Matrix(Shader &shader, const char *uniform);

        // Input function handles all the inputs from the window
        void Inputs(GLFWwindow* window);
};


#endif