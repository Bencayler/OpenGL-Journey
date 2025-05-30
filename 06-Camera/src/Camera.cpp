#include "Camera.h"


Camera::Camera(int width, int height, glm::vec3 position) {
    this->width  = width;
    this->height = height;

    this->Position = position;

}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader &shader, const char* uniform) {
    glm::mat4 view       = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(Position, Position + Orientation, Up);
    
    
    projection = glm::perspective(
			glm::radians(45.0f), // Field of view in degrees
		    static_cast<float>(width) / static_cast<float>(height),     // Aspect ratio (the same as the window size)
			0.1f,                // Near visible plane
			1000.0f              // Far visible plane
		);

    glUniformMatrix4fv(
        glGetUniformLocation(shader.getProgramID(), uniform), 
                             1, 
                             GL_FALSE, 
                             glm::value_ptr(projection * view)
    );
}

// Camera inputs for movement of the camera! Yay! Something really exciting! 
void Camera::Inputs(GLFWwindow* window) {
    // Change the position of the camera based on the inputted key
    // If shift is help down the speed should increase
    // Add comments of how this works with the cross product

    // Handle key inputs
    // TODO: W key for forward == Complete
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        Position += speed * Orientation;
    }
    
    // TODO: S key for backward == Complete
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        Position += speed * -Orientation;
    }

    // TODO: A key for left == Complete
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        Position += speed * -glm::normalize(glm::cross(Orientation, Up));
    }

    // TODO: D key for right == Complete
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        Position += speed * glm::normalize(glm::cross(Orientation, Up));
    }
 
    // TODO: Space key for up == Complete
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        Position += speed * Up;
    }

    // TODO: Left control for down == Complete
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        Position += speed * -Up;
    }

    // TODO: Left shift for speed increase == Complete
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        speed = 0.4f;
    } 
    // TODO: If left shift is released change the speed back to normal
    // NOTICE THE RELEASE ENUM
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
        speed = 0.1f;
    }

    // Handle mouse inputs
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        // Hide the mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);


        // Store the coordinates of the cursor
        double mouseX;
        double mouseY;
        // Fetch the coordinates of the cursor - pass by reference so the 
        // changes are retained across every frame of the rendering loop
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Normalizes and shifts the coordinates of the cursor such that they
        // begin in the middle of the sceen then "transform" them into degrees
        float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
        float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

        // Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
}