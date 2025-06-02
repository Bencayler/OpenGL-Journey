#version 330 core
out vec4 fragColor; // Output color to the framebuffer

uniform vec4 lightColor;

void main() {
	// Notice the color 
	fragColor = lightColor;

}