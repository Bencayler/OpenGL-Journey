#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 vertexColor;

// Uniform matrices
uniform mat4 mModel;
uniform mat4 mView; 
uniform mat4 mProjection;


void main() {
	
	gl_Position = mProjection * mView * mModel * vec4(aPos, 1.0);
	// gl_Position = vec4(aPos, 1.0);
	
	vertexColor = aColor;
}