#version 330 core


in vec3 vertexColor; // Input from vertex shader
out vec4 fragColor; // Output color to the framebuffer


void main() {
	fragColor = vec4(vertexColor, 1.0);
}