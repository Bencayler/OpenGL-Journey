#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
out vec3 vertexColor;

// attribute vec3 vertPosition;
// May not be necessary if using gl_Position directly



void main() {
	gl_Position = vec4(aPos, 1.0);
	vertexColor = aColor;
}