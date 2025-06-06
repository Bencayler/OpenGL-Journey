#version 330 core
// Setup layout for the lighting shader program
layout(location = 0) in vec3 aPos;



uniform mat4 camMatrix;
uniform mat4 modelMatrix;


void main() {
	
	gl_Position = camMatrix *  modelMatrix * vec4(aPos, 1.0);

}