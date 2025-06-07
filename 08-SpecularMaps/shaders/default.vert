#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;


// Outputs the texture coordinates to the fragment shader
out vec2 textureCoords;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 modelMatrix;
uniform mat4 camMatrix;


void main() {
	// Calculate fragment position in world space
	FragPos = vec3(modelMatrix * vec4(aPos, 1.0));

	// Transform normal to world space (important for correct lighting
	// Using rtanspose(inverse(modelMatrix)) handles non-uniform scaling correctly
	Normal = mat3(transpose(inverse(modelMatrix))) * aNormal;
	textureCoords = aTexCoord;
	
	gl_Position = camMatrix *  modelMatrix* vec4(aPos, 1.0);
	// gl_Position = vec4(aPos, 1.0);
	
	
}