#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;


// Outputs the texture coordinates to the fragment shader
out vec2 textureCoords;


uniform mat4 camMatrix;


void main() {
	
	gl_Position = camMatrix *  vec4(aPos, 1.0);
	// gl_Position = vec4(aPos, 1.0);
	
	textureCoords = aTexCoord;
}